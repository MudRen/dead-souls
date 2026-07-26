/*    /domains/Ylsrim/etc/hole.c
 *    From the Dead Souls Mud Library
 *    An example of something people can jump into
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>
#include <jump.h> // defines JUMP_INTO

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_JUMP; // This makes it jumpable

protected void create() {
    dummy::create();
    SetKeyName("hole");
    SetId("hole", "bank");
    SetShort("屋顶上的一个洞");
    SetLong("银行内部太暗看不清楚，但也许你可以跳进去？");
    AddJump("hole","/domains/Ylsrim/room/bank", JUMP_INTO);
}
