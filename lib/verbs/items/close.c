/*    /verbs/items/close.c
 *    from the Dead Souls Mud Library
 *    close OBJ
 *    created by Descartes of Borg 960115
 *    Version: @(#) close.c 1.2@(#)
 *    Last modified: 96/10/15
 */

#include <lib.h>
#include "include/close.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("close");
    SetRules("OBJ");
    SetSynonyms("shut");
    SetErrorMessage("关闭什么？");
    SetHelp("用法：close <物品>\n\n"
            "关闭门、箱子或其他类似的物品。\n\n"
            "同义词：shut\n\n"
            "另见：lock, open, pick, unlock");
}

mixed can_close_obj(string verb) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

varargs mixed do_close_obj(object ob, mixed *args...) {
    string what;

    what = remove_article(lower_case(args[0]));
    return ob->eventClose(this_player(), what);
}
