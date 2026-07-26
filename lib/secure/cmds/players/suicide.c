/*  /secure/cmds/player/suicide.c
 *  from the Dead Souls Object Library
 *  Allows players to obliterate their character
 *  created by Blitz@Dead Souls
 */

#include <lib.h>
#include <dirs.h>
#include <flags.h>
#include <privs.h>
#include <daemons.h>
#include ROOMS_H
#include <message_class.h>

inherit LIB_DAEMON;

private void GetPassword(string input);
private void GetYesOrNo(string input);
private void EndSuicide(string who);

string home_dir = "";
string newfile, tmp, gwho = "";

int eventHoseDude(object dude){
    if(dude) dude->eventDestruct();
    if(dude) destruct(dude);
    return 1;
}

mixed cmd(string str) {
    string who;
    object ob;

    if( sizeof(str) ) return "自杀命令不需要任何参数。";
    ob = previous_object();
    if( this_player(1) != ob || !userp(ob) ) {
        log_file("security", "** Illegal suicide attempt **\n "
                "Call stack:\n"+ sprintf("%O\n", previous_object(-1)));
        return "自杀失败。";
    }
    if( this_player()->GetForced() ) {
        log_file("security", "*** Illegal \"Forced\" Suicide **\n"
                "Call stack:\n"+ sprintf("%O\n", previous_object(-1)));
        return 0;
    }
    who = this_player()->GetKeyName();
    if( who == "guest" ) return "访客不能自杀！";
    if( member_group(who, PRIV_SECURE) || member_group(who, PRIV_ASSIST) )
        return "你必须先被取消安全权限才能自杀。";
    this_player()->eventPrint("自杀意味着你的角色将从"+mud_name()+"的数据库中完全删除。"
            "如果你确定要这样做，请输入你的正确密码。"
            "否则请输入一个错误的密码。");
    this_player()->eventPrint("密码：", MSG_EDIT);
    input_to((: GetPassword :), I_NOECHO | I_NOESC);
    return 1;
}

private void GetPassword(string input) {
    string tmp;
    if( !sizeof(input) ) {
        this_player()->eventPrint("自杀已取消。");
        return;
    }
    tmp = this_player()->GetPassword();
    if( tmp != crypt(input, tmp) ) {
        this_player()->eventPrint("密码错误。自杀已取消。");
        return;
    }
    this_player()->eventPrint("\n留下遗书吗？(a)放弃, (y)是, (N)否 :\n",
            MSG_EDIT);
    input_to((: GetYesOrNo :));
    return;
}

private void GetYesOrNo(string input) {
    tmp = this_player()->GetKeyName();
    if( !sizeof(input) || (input = lower_case(input))[0] != 'y' ) {
        if( input && input[0] == 'a' ) {
            this_player()->eventPrint("自杀已取消。");
            return;
        }
        EndSuicide(tmp);
        return;
    }
    this_player()->eventPrint("\n你现在可以写一封遗书来解释你自杀的原因。"
            "如果你不想写遗书，只需退出编辑器即可。"
            "（在空白行输入\".\"退出编辑器。）\n");
    this_player()->eventEdit(DIR_TMP + "/" + tmp, (: EndSuicide, tmp :));
}

private void EndSuicide(string who) {
    string file;
    object *ob;
    string whocheck = cleaned_end(base_name(this_player()));
    tmp = "";
    newfile = "";
    if(who != whocheck){
        write("身份验证出现冲突。");
        write("自杀已取消。");
        return;
    }
    gwho = who;
    home_dir = homedir(this_player());
    if(!directory_exists(DIR_TMP + "/suicide/")) mkdir (DIR_TMP + "/suicide/");

    file = DIR_TMP + "/" + who;
    newfile = "/log/suicides/" + who;
    if( file_size(file) > 0 ) {
        tmp = possessive_noun(who)+" suicide note.\n"
            "Dated: "+ctime(time())+"\n";
        tmp += read_file(file);
        if(!directory_exists("/log/suicides")){
            unguarded( (: mkdir("/log/suicides") :) );
        }
        unguarded( (: write_file(newfile, tmp, 1) :) );
    }
    if( file_exists(file) ) rm(file);
    log_file("suicide", who+" suicided at "+ctime(time())
            +". (from "+query_ip_name(this_player())+")\n");
    tmp = player_save_file(who);
    unguarded((: rename, tmp, save_file(DIR_SUICIDE + "/" + who) :));
    if(home_dir && directory_exists(home_dir)){
        object *purge_array = filter(objects(), (: !strsrch(base_name($1), home_dir) :) );
        foreach(object tainted in purge_array){
            if(clonep(tainted)){
                tainted->eventMove(ROOM_FURNACE);
                purge_array -= ({ tainted });
            }
        }
        foreach(object tainted in purge_array){
            tainted->eventDestruct();
        }
        unguarded( (: rename(home_dir,"/secure/save/decre/"+gwho+"."+timestamp()) :) );
        home_dir = "";
        gwho = "";
    }
    this_player()->eventPrint("你已经自杀了。欢迎下次再来。");
    environment(this_player())->eventPrint(
            this_player()->GetName()+"在你面前结束了自己的生命。",
            this_player() );
    if( sizeof( ob = filter(users(), (: archp :)) ) )
        ob->eventPrint("["+this_player()->GetName()+"自杀了]");
    PLAYERS_D->RemoveUser(who);
    this_player()->eventMove(ROOM_FURNACE);
    this_player()->eventDestruct();
    return;
}

string GetHelp(){
    return "命令格式：suicide\n\n"
        "结束你在"+mud_name()+"上的角色存在，此操作不可逆转。"
        "一旦你发出此命令，系统会要求你输入密码确认身份。"
        "密码确认后，你将从数据库中被删除。"
        "你也可以选择留下遗书。\n\n"
        "注意：如果你从受限站点自杀，你需要重新注册！";
}
