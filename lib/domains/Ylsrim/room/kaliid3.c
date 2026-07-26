/*    /domains/Ylsrim/room/kaliid3.c
 *    From the Dead Souls Mud Library
 *    An example of a room with a door and press event handler
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("卡利德路教堂旁");
    SetLong("卡利德路从东向西穿过沙漠小镇伊尔斯利姆。"
            "路面越往东越沙化，逐渐被远处的沙漠吞没。"
            "在路的北端，有一扇属于当地教堂的门。"
            "门旁边有一个巨大的按钮。");
    SetSkyDomain("town");
    AddItem("church", "这是一座相当简陋的木制建筑，当地牧师在这里为人们举行入教仪式。");
    AddItem("desert", "小镇竭尽全力防止被沙漠吞没。");
    AddItem(new("/domains/Ylsrim/etc/church_button"));
    SetExits( ([ 
                "north" : "/domains/Ylsrim/room/"+ "church",
                "west" : "/domains/Ylsrim/room/"+ "kaliid4" ]));
    SetDoor("north", "/domains/Ylsrim/etc/church_door");
}

void init(){
    ::init();
}
