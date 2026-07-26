/*    /daemon/party.c
 *    from the Dead Souls  Object Library
 *    manages parties
 *    created by Descartes of Borg 951120
 */

#include <lib.h>
#include <save.h>
#include <daemons.h>
#include <message_class.h>
#include "include/party.h"

inherit LIB_DAEMON;

mapping Parties;
nosave string SaveFile;
string *old_parties;

protected void create() {
    daemon::create();
    SaveFile = save_file(SAVE_PARTIES);
    Parties = ([]);
    old_parties = ({});
    if( unguarded((: file_exists(SaveFile) :)) ){
        RestoreObject(SaveFile);
    }
    SetNoClean(1);
    this_object()->eventCleanParties();
    set_heart_beat(60);
    SaveObject(SaveFile);
}

protected void eventDestroyParty(string party){
    if(!party || !Parties[party]) return;
    foreach(mixed member in this_object()->GetPartyMembers(party)){
        if(member){
            member->SetParty(0);
        }
    }
    if(member_array(party, CHAT_D->GetLocalChannels()) != -1){
        CHAT_D->eventSendChannel("System", party, "队伍 " + party +
                " 已经解散。");
        CHAT_D->RemoveLocalChannel(party);
    }
    map_delete(Parties, party);
    old_parties = distinct_array( (old_parties || ({})) + ({ party }) );
    SaveObject(SaveFile);
}

string *GetOldParties(){
    return sort_array((copy(old_parties || ({})) - keys(Parties || ([]))),1);
}

protected void eventCleanParties(){
    foreach(mixed key, mixed val in Parties){
        mixed* members = this_object()->GetPartyMembers(key);
        members -= ({ 0 });
        if(!sizeof(members)) eventDestroyParty(key);
    }
}

void heart_beat(){
    eventCleanParties();
}

mixed* GetParties(){
    return keys(Parties);
}

mapping GetPartiesMap(){
    return copy(Parties);
}

mixed CanChangeLeader(object who, object targ) {
    class party p;
    string pname;

    if( !(p = Parties[pname]) ) return "不存在此队伍。";
    if( p->Leader != who )
        return "您必须是队长才能更换队长。";
    if( member_array(targ, p->Members) == -1 )
        return targ->GetName() + " 不在队伍中。";
    SaveObject(SaveFile);
    return 1;
}

mixed CanCreateParty(object who, string name) {
    string *tmpnames = ( CHAT_D->GetChannels() || ({}) );
    tmpnames += ({ "party", "lemon" });
    if( Parties[name] ) return "已存在同名的队伍。";
    if( member_array(name, tmpnames) != -1 )
        return "您不能使用 " + name + " 作为队伍名称。";
    if( who->GetParty() ) return "您已经在队伍中了！";
    eventSave();
    return 1;
}

mixed CanInviteMember(object who, object member) {
    string pname;

    pname = who->GetParty();
    if( !Parties[pname] ) return "不存在此队伍！";
    if( ((class party)Parties[pname])->Leader != who )
        return "只有队长才能邀请成员！";
    if( member->GetParty() )
        return member->GetName() + " 已经在队伍中了。";
    if( environment(member) != environment(who) )
        return member->GetName() + " 必须在您附近。";
    return 1;
}

mixed CanJoinParty(object who, string pname) {
    if( !Parties[pname] ) return "不存在此队伍。";
    if( member_array(who, ((class party)Parties[pname])->Invited) == -1 )
        return "您没有被邀请加入该队伍。";
    if( who->GetParty() ) return "您已经在队伍中了。";
    if( environment(who) != environment(((class party)Parties[pname])->Leader) )
        return "您不在队长附近。";
    return 1;
}

mixed CanLeaveParty(object who) {
    class party p;
    string pname;

    pname = who->GetParty();
    if( !pname || !(p = Parties[pname]) ) return "不存在此队伍。";
    if( member_array(who, p->Members) == -1 )
        return "您不在该队伍中。";
    return 1;
}

mixed CanRemoveMember(object who, object targ) {
    class party p;
    string pname;

    pname = who->GetParty();
    if( !(p = Parties[pname]) ) return "不存在此队伍。";
    if( p->Leader != who ) return "只有队长才能移除成员。";
    return 1;
}

mixed CanRemoveParty(object who) {
    class party p;
    string pname;

    pname = who->GetParty();
    if( !(p = Parties[pname]) ) return "不存在此队伍！";
    if( p->Leader != who )
        return "只有队长才能解散队伍。";
    return 1;
}

mixed eventChangeLeader(object who, object targ) {
    class party p;
    string pname;

    pname = who->GetParty();
    p = Parties[pname];
    p->Leader = targ;
    CHAT_D->eventSendChannel("System", pname, targ->GetName() + " 现在是队长了。");
    SaveObject(SaveFile);
    return 1;
}

mixed eventCreateParty(object who, string name) {
    class party this_party;

    if( who->SetParty(name) != name )
        return "将您加入队伍时出现异常问题。";
    this_party = new(class party);
    this_party->Leader = who;
    this_party->Members = ({ who });
    this_party->Invited = ({});
    Parties[name] = this_party;
    who->eventPrint("队伍 " + name + " 创建成功。", MSG_SYSTEM);
    SaveObject(SaveFile);
    return 1;
}

mixed eventInviteMember(object who, object targ) {
    class party this_party;
    string name;

    name = who->GetParty();
    this_party = Parties[name];
    this_party->Invited += ({ targ });
    CHAT_D->eventSendChannel("System", name, targ->GetName() +
            " 被邀请加入队伍。");
    call_out((: RemoveInvitiation :), 60, name, targ);
    targ->eventPrint("您被邀请加入队伍 \"" + name +
            "\"。\n请在60秒内输入 \"party join " + name + "\" 加入队伍。", MSG_SYSTEM);
    SaveObject(SaveFile);
    return 1;
}

mixed eventJoinParty(object who, string name) {
    class party this_party;
    mixed tmp;

    if( (tmp = CanJoinParty(who, name)) != 1 ) return tmp;
    this_party = Parties[name];
    if( who->SetParty(name) != name )
        return "加入队伍时出现错误。";
    this_party->Invited -= ({ who });
    this_party->Members += ({ who });
    CHAT_D->eventSendChannel("System", name, who->GetName() +
            " 加入了队伍。");
    SaveObject(SaveFile);
    return 1;
}

mixed eventLeaveParty(object who) {
    mixed ret = eventRemoveMember(who, who);
    SaveObject(SaveFile);
    return ret;
}

mixed eventRemoveMember(object who, object targ) {
    class party p;
    object ob = 0;
    string name;

    p = Parties[name = who->GetParty()];
    if( targ == p->Leader ) {
        if( sizeof(p->Members) == 1 ) return eventRemoveParty(who);
        else {
            foreach(ob in p->Members) if( ob != targ ) break;
            if( !ob ) return eventRemoveParty(who);
            else {
                p->Leader = ob;
                ob->eventPrint("您现在是队伍 " + name + " 的队长了。", MSG_SYSTEM);
            }
        }
    }
    targ->SetParty(0);
    if( Parties[name] ) {
        p->Members -= ({ targ });
        CHAT_D->eventSendChannel("System", name, targ->GetName() +
                " 已离开队伍。");
    }
    targ->eventPrint("您不再是队伍 " + name + " 的成员了。", MSG_SYSTEM);
    SaveObject(SaveFile);
    return 1;
}

mixed eventRemoveParty(object who) {
    string name = who->GetParty();
    eventDestroyParty(name);
    return 1;
}

object GetPartyLeader(string name) {
    class party p;
    string nom;

    foreach(nom, p in Parties) if( nom == name ) return p->Leader;
    return 0;
}

object *GetPartyMembers(string name) {
    class party p;
    string nom;

    foreach(nom, p in Parties) if( nom == name ) return p->Members;
    return 0;
}

protected void RemoveInvitiation(string name, object who) {
    if( !Parties[name] ) return;
    if( member_array(who, ((class party)Parties[name])->Invited) == -1 )
        return;
    ((class party)Parties[name])->Invited -= ({ who });
}
