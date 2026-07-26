/*    /verbs/creators/echo.c
 *    from the Dead Souls Mud Library
 *    echo
 *    echo STR
 *    echo to LIV STR
 *    created by Descartes of Borg 951114
 */

#include <lib.h>
#include <message_class.h>
#include "include/echo.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("echo");
    SetRules("","to LIV STR","STR");
}

int livings_are_remote() { return 1; }

mixed can_echo() {
    if( !creatorp(this_player()) ) return 0;
    else return "回显什么？对谁回显什么？对所有人回显什么？";
}

mixed can_echo_to_liv_str(object ob, string str) {
    if( !ob || !str ) return 0;
    if( !creatorp(this_player()) ) return 0;
    return 1;
}

mixed can_echo_str(string str) {
    if( !str || !creatorp(this_player()) ) return 0;
    return 1;
}

mixed do_echo() { return 1; }

mixed do_echo_to_liv_str(object who, string what) {
    eventEcho(({ who }), what);
    return 1;
}

mixed do_echo_str(string str) {
    object *obs;
    string tmp;

    if( sscanf(str, "to all %s", tmp) && tmp ) {
        obs = (users() - ({ this_player() }));
        str = tmp;
    }
    else obs = (all_inventory(environment(this_player())) - ({this_player()}));
    eventEcho(obs, str);
    return 1;
}

void eventEcho(object *targs, string str) {
    object ob;

    foreach(ob in targs) {
        if( archp(ob) )
            ob->eventPrint(this_player()->GetCapName() +
                    " echoes: " + str, MSG_CONV);
        else ob->eventPrint(str, MSG_CONV);
    }
    this_player()->eventPrint("你回显：" + str, MSG_CONV);
}

string GetHelp(string str) {
    return ("用法：echo <消息>\n"
            "      echo to <生物> <消息>\n"
            "      echo to all <消息>\n\n"
            "如果你没有指定回显对象，将向房间内的所有人发送不带前缀的消息。"
            "你也可以向游戏中的所有人回显。滥用此命令严重违反 MUD 道德。\n"
            "另见：say, tell");
}
