/*    /cmds/creator/clean.c
 *    From the Dead Souls Mud Library
 *    Cleans out the inventory of an object, defaulting to this room
 *    created by Valodin@Dead Souls 930101
 *    Version: @(#) clean.c 1.2@(#)
 *    Last modified: 96/10/06
 */

#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object* obs, items, users;
    object ob;

    if( !args || args == "" ) {
        ob = environment(previous_object());
    }
    else {
        ob = get_object(args);
    }
    if( !ob ) {
        return "未找到 " + args + "。";
    }
    previous_object()->eventPrint(sprintf("Cleaning %O", ob), MSG_SYSTEM);
    say(this_player()->GetName()+" cleans "+ob->GetShort()+".");
    obs = deep_inventory(ob);
    users = filter(obs, (: userp :));
    items = obs - users;
    foreach(object user in users) {
        object tmp = user;

        while( tmp = environment(tmp) ) {
            items -= ({ tmp });
        }
    }
    foreach(object item in items) {
        if( item ) {
            item->eventDestruct();
        }
    }
    return 1;
}

string GetHelp() {
    return ("语法：clean [对象]\n\n"
            "此命令销毁指定对象库存中的所有物品。"
            "会跳过深层库存中包含用户的任何物品。");
}
