/*    /verbs/items/unlock.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951028
 *    Version: @(#) unlock.c 1.3@(#)
 *    Last modified: 97/01/02
 */

#include <lib.h>
#include "include/unlock.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("unlock");
    SetRules("OBJ with OBJ", "OBJ with STR");
    SetErrorMessage("用什么解锁什么？");
    SetHelp("用法：unlock <物品> with <钥匙>\n\n"
            "第一个物品是你想要解锁的东西，比如门或箱子。第二个是你想要用来解锁的钥匙。"
            "如果你的钥匙是对的，那么 unlock 命令就会把它解锁。\n\n"
            "另见：close, lock, open, pick");
}

varargs mixed can_unlock_obj_with_obj(object foo, object bar,
        mixed words...) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

varargs mixed can_unlock_obj_with_str(mixed ob1, mixed ob2, mixed words...) {
    object wut = get_object(ob2);
    if(wut) ob2 = wut->GetKeyName();
    return can_unlock_obj_with_obj(ob1, ob2, words[1], ob2);
}

varargs mixed do_unlock_obj_with_obj(object ob1, object ob2, mixed args...) {
    return ob1->eventUnlock(this_player(), ob2);
}

varargs mixed do_unlock_obj_with_str(mixed ob1, mixed ob2, mixed words...) {
    return do_unlock_obj_with_obj(ob1, (get_object(lower_case(ob2)) || ""));
}

