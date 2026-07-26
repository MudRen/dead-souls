/*    /domains/Ylsrim/etc/wall.c
 *    From the Dead Souls Mud Library
 *    An example of climbing up
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>
#include <climb.h> // defines CLIMB_UP

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_CLIMB; // This makes it climbable

protected void create() {
    dummy::create();
    SetKeyName("wall");
    SetId("wall");
    SetAdjectives("adobe", "bank");
    SetShort("一面土坯墙");
    SetLong("墙上有足够的孔洞，你可以找到好的落脚点攀爬上去！");
    SetClimb("/domains/Ylsrim/room/bank_roof", CLIMB_UP);
}
