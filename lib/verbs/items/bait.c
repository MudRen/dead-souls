/*  /verbs/items/bait.c
 *  from the Dead Souls Mud Library
 *  bait verb used with /lib/bait.c
 *  created by Blitz@Dead Souls 960117
 */



#include <lib.h>
#include "include/bait.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("bait");
    SetRules("OBJ with OBJ");
    SetErrorMessage("用什么给什么上饵？");
    SetHelp("Syntax: bait <POLE> with <BAIT>\n\n"
            "The bait command is normally used to fasten bait onto "
            "a fishing pole.  The POLE must be a device of some "
            "kind which is used for catching fish.  The BAIT "
            "must be some sort of fishing bait.");
}

mixed can_bait_obj_with_obj(string verb) { return this_player()->CanManipulate(); }

mixed do_bait_obj_with_obj(object pole, object bait) {
    if( pole == bait ) {
        this_player()->eventPrint("你不能用它给自己上饵！");
        return 1;
    }
    return bait->eventBait(this_player(), pole);
}
