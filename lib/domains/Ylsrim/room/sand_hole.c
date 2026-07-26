/*    /domains/Ylsrim/room/sand_hole.c
 *    From the Dead Souls Mud Library
 *    An example of a room in which you go after digging (get trapped!)
 *    Created by Descartes of Borg 961231
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(25);
    SetShort("沙中的一个黑暗洞穴");
    SetLong("你身处沙漠中一个非常黑暗的沙洞里。");
    AddItem("sand", "沙子无处不在。");
    SetObviousExits("");
    SetExits( ([ "up" : "/domains/Ylsrim/room/"+ "sand_room" ]));
    // use a door to act as a hole, as that is what the hole really is
    SetDoor("up", "/domains/Ylsrim/etc/dug_hole");
}
void init(){
    ::init();
}
