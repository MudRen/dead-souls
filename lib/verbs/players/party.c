/*    /verbs/players/party.c
 *    from the Dead Souls  Object Library
 *    party
 *    party WRD
 *    party WRD WRD
 *    party WRD LIV
 *    created by Descartes of Borg 951121
 */

#include <lib.h>
#include <daemons.h>
#include "include/party.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("party");
    SetRules("WRD", "WRD WRD", "WRD LIV");
    SetErrorMessage("你必须指定一个动作，请参阅\"help party\"。");
}

int livings_are_remote() { return 1; }

mixed can_party_wrd(string cmd) {
    if( !cmd ) return 0;
    switch( cmd ) {
        case "disband":
            return PARTY_D->CanRemoveParty(this_player());

        case "leave":
            return PARTY_D->CanLeaveParty(this_player());

        default:
            return "那似乎不是你能做的。";
    }
}

mixed can_party_wrd_wrd(string cmd, string party) {
    if( !cmd || !party ) return 0;
    if(cmd == "invite"){
        if(!party || !present(party,environment(this_player()))){
            return "那个人不在这里。";
        }
        if(!living(present(party,environment(this_player())))){
            return "那不是活物。";
        }
    }
    switch(cmd) {
        case "create":
            return PARTY_D->CanCreateParty(this_player(), party);

        case "join":
            return PARTY_D->CanJoinParty(this_player(), party);

        default:
            return "不能那样操作。";
    }
}

mixed can_party_wrd_liv(string cmd) {
    if( !cmd ) return 0;    
    switch(cmd) {
        case "invite":
        case "leader":
        case "remove":
            return 1;

        default:
            return "那是未知的队伍动作。";
    }
}

mixed do_party_wrd(string cmd) {
    switch(cmd) {
        case "disband":
            return PARTY_D->eventRemoveParty(this_player());

        case "leave":
            return PARTY_D->eventLeaveParty(this_player());
    }
}

mixed do_party_wrd_wrd(string cmd, string party) {
    switch(cmd) {
        case "create":
            return PARTY_D->eventCreateParty(this_player(), party);

        case "join":
            return PARTY_D->eventJoinParty(this_player(), party);
    }
}

mixed do_party_wrd_liv(string cmd, object targ) {
    mixed foo;
    switch(cmd) {
        case "invite":
            foo = PARTY_D->CanInviteMember(this_player(), targ);
            break; 
        case "leader":
            foo = PARTY_D->CanChangeLeader(this_player(), targ);
            break;    
        case "remove":
            foo = PARTY_D->CanRemoveMember(this_player(), targ);
            break;
        default:
            return "你未能做到。";
    }
    if( stringp(foo) ) 
        return this_player()->eventPrint(foo), 1;    
    if( !foo || !intp(foo) ) return foo;
    switch(cmd) {
        case "invite":
            return PARTY_D->eventInviteMember(this_player(), targ);

        case "leader":
            return PARTY_D->eventChangeLeader(this_player(), targ);

        case "remove":
            return PARTY_D->eventRemoveMember(this_player(), targ);
    }
}

string GetHelp(string str) {
    return ("Syntax: party create <PARTY>\n"
            "        party disband\n"
            "        party invite <PLAYER>\n"
            "        party join <PARTY>\n"
            "        party leader <PLAYER>\n"
            "        party leave\n"
            "        party remove <PLAYER>\n\n"
            "This command is the interface to the Dead Souls party system.  "
            "A party is simply a group of players who are adventuring "
            "together.  The advantage of a party is that it allows people "
            "to share the bounties of a quest or other such venture "
            "together. It allows such things as group completions of quests. "
            "For example, if the party completes a quest, each member of the "
            "party is credited with completing the quest.  Note that in "
            "order to get such credit, the party must be together upon "
            "completion of the quest.\n\nNOTE: In order to invite someone "
            "into your party, they must be in the same room as you. Also, "
            "joining a party does not mean you automatically follow the "
            "leader. To do that, you must use the \"lead\" and \"follow\" "
            "commands.");
}
