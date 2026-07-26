/*    /verbs/items/lock.c
 *    from the Dead Souls Mud Library
 *    lock OBJ with OBJ
 *    created by Descartes of Borg 951028
 *    Version: @(#) lock.c 1.2@(#)
 *    Last modified: 96/10/15
 */

#include <lib.h>
#include "include/lock.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("lock");
    SetRules("OBJ with OBJ","OBJ with STR");
    SetErrorMessage("用什么锁什么？");
    SetHelp("用法：lock <物品> with <钥匙>\n\n"
            "第一个物品是你想要锁住的东西，比如门或箱子。第二个是你想要用来锁的钥匙。"
            "如果你的钥匙是对的，那么 lock 命令就会把它锁上。\n\n"
            "另见：close, open, pick, unlock");
}

varargs mixed can_lock_obj_with_obj(mixed ob1, mixed ob2,
        mixed mix1, mixed mix2) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

varargs mixed can_lock_obj_with_str(mixed ob1, mixed ob2, mixed words...) {
    object wut = get_object(ob2);
    if(wut) ob2 = wut->GetKeyName();
    return can_lock_obj_with_obj(0, 0, words...);
}

varargs mixed do_lock_obj_with_obj(object target, object key, mixed words...) {
    if (sizeof(words))
    {
        string id;
        id = remove_article(lower_case(words[0]));
        return target->eventLock(this_player(), id, key);
    }
    return target->eventLock(this_player(), key);
}

varargs mixed do_lock_obj_with_str(mixed ob1, mixed ob2, mixed words...) {
    return do_lock_obj_with_obj(ob1, (get_object(lower_case(ob2)) || ""));
}
