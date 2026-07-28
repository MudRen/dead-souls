/*    /verbs/players/request.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951219
 */

#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("request");
    SetRules("STR from LIV");
    SetErrorMessage("向谁请求什么？");
    SetHelp("Syntax: request <SOMETHING> from <LIVING>\n\n"
            "This allows you to ask livings things for particular things.  "
            "For example, in Newbieland, you might 'request clothes from "
            "man'.  This command behaves identically to 'ask LIVING for "
            "SOMETHING'.\n"
            "See also: ask");
}

mixed can_request_str_from_liv() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    else {
        return 1;
    }
}

mixed do_request_str_from_liv(string str, object who) {
    this_player()->eventPrint("你向" +
            who->GetName() + "请求" + str + "。");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "向" + who->GetName() + "请求" +
            str + "。",
            ({ who, this_player() }));
    if( !(who->eventRequest(this_player(),
                    remove_article(lower_case(str)))) )
        who->eventPrint(this_player()->GetName() + "向你请求" +
                str + "。");
    return 1;
}
