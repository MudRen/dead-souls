/*    /domains/Ylsrim/etc/roof.c
 *    From the Dead Souls Mud Library
 *    An example of something people can jump from
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>
#include <jump.h> // defines JUMP_FROM

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_JUMP; // This makes it jumpable

protected void create() {
    dummy::create();
    SetKeyName("roof");
    SetId("roof");
    SetAdjectives("adobe", "bank");
    SetShort("屋顶");
    SetLong("银行屋顶俯瞰着下面的道路。"
            "也许你可以跳下去。"
            "土坯墙看起来可以攀爬下去。");
    //"A hole in the center of the roof opens into the bank.");
    AddJump("roof","/domains/Ylsrim/room/bank", JUMP_FROM);
}
