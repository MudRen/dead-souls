/*    /domains/Ylsrim/etc/road.c
 *    From the Dead Souls Mud Library
 *    An example of something people can jump into
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>
#include <jump.h> // defines JUMP_INTO
#include <damage_types.h> // defines BLUNT

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_JUMP; // This makes it jumpable

int eventJump(object who) {
    who->eventReceiveDamage(0, BLUNT, random(100) + 5, 1);
    who->eventMoveLiving("/domains/Ylsrim/room/kaliid6",
            "$N试图跳到路上，结果" + reflexive(who) + "受了重伤。",
            "$N从天上掉了下来。");
    return 1;
}

protected void create() {
    dummy::create();
    SetKeyName("road");
    SetId("road");
    SetAdjectives("kaliid");
    SetShort("卡利德路", 1); // it is a proper noun
    SetLong("穿过伊尔斯利姆的主要道路。");
    AddJump("road","/domains/Ylsrim/room/kaliid6",JUMP_INTO);
}
