/*    /domains/Ylsrim/etc/roof_wall.c
 *    From the Dead Souls Mud Library
 *    An example of climbing down
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>
#include <climb.h> // defines CLIMB_DOWN

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_CLIMB; // This makes it climbable

protected void create() {
    dummy::create();
    SetKeyName("wall");
    SetId("wall");
    SetAdjectives("adobe", "bank");
    SetShort("一面土坯墙");
    SetLong("墙上有足够的孔洞，你可以找到好的落脚点攀爬下去！");
    SetClimb("/domains/Ylsrim/room/kaliid6", CLIMB_DOWN);
}
