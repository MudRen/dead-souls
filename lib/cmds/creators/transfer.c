/*    /cmds/creators/transfer.c
 *    From the Dead Souls Mud Library
 *    Moves object from one place to another
 *    created by Descartes of Borg 961008
 *    Version: @(#) transfer.c 1.2@(#)
 *    Last modified: 96/10/08
 */

#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object what, destination;
    string a, b;
    mixed res;

    if(!args || args == ""){
        return "语法：<transfer 物品 into 容器>\n\n";
    }

    if( sscanf(args, "%s into %s", a, b) != 2 &&
            sscanf(args, "%s to %s", a, b) != 2 ) {
        return "语法：<transfer 物品 into 容器>\n\n";
    }
    what = get_object(a);
    destination = get_object(b);
    if( !what ) {
        return "找不到 " + a + "。";
    }
    if( !destination ) {
        return "找不到 " + b + "。";
    }
    if( living(what) && living(destination) ) {
        return "不能这样做。";
    }
    res = what->eventMove(destination);
    if( !res ) {
        return "无法将 " + identify(what) + " 转移到 " +
            identify(destination) + "。";
    }
    else if( res != 1 ) {
        return res;
    }
    previous_object()->eventPrint("已将 " + identify(what) + " 转移到 " +
            identify(destination) + "。", MSG_SYSTEM);
    if( living(what) ) {
        what->eventDescribeEnvironment();
    }
    return 1;
}

string GetHelp() {
    return ("语法：transfer <物品 into 容器>\n\n"
            "允许你将指定物品转移到指定容器中。\n"
            "另见：trans, expel, goto, return");
}
