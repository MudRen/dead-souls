/*    /verbs/items/open.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960115
 *    Version: @(#) open.c 1.2@(#)
 *    Last modified: 96/10/15
 */

#include <lib.h>
#include "include/open.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("open");
    SetRules("OBJ", "OBJ with OBJ");
    SetErrorMessage("打开什么？或者用什么打开什么？");
    SetHelp("用法：open <物品>\n"
            "      open <物品> with <工具>\n\n"
            "打开门、箱子或其他类似的物品。有些东西可以使用能强行打开的工具来打开。\n\n"
            "另见：close, lock, pick, unlock");
}

mixed can_open_obj(string verb, string id) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

mixed can_open_obj_with_obj(string verb, string id1, string id2) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

varargs mixed do_open_obj(object ob, mixed *args...) {
    string what;

    what = remove_article(lower_case(args[0]));
    return ob->eventOpen(this_player(), what);
}

varargs mixed do_open_obj_with_obj(object ob, object with, mixed *args...) {
    string what;

    what = remove_article(lower_case(args[0]));
    return ob->eventOpen(this_player(), what, with);
}
