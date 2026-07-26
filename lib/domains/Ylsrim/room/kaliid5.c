/*    /domains/Ylsrim/room/kaliid5.c
 *    From the Dead Souls Mud Library
 *    A simple room 
 *    Created by Descartes of Borg 960512
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("卡利德路战士大厅附近");
    SetLong("卡利德路向东西方向延伸，横跨伊尔斯利姆，一望无际。"
            "在这段路的北侧坐落着当地的战士大厅。"
            "入口内你立刻注意到一个招募区，"
            "初出茅庐的寻宝者在这里决定成为战士。");
    SetSkyDomain("town");
    AddItem("hall", "经过伊尔斯利姆的战士们停下来闲聊他们的冒险经历，新人们报名成为战士。",
            ({ "fighter", "fighters" }));
    AddItem("road", "伊尔斯利姆的主要街道。", ({ "kaliid" }));
    SetExits( ([ "east" : "/domains/Ylsrim/room/"+ "kaliid4",
                "west" : "/domains/Ylsrim/room/"+ "kaliid6",
                "north" : "/domains/Ylsrim/room/"+ "fighter_hall" ]));
}
void init(){
    ::init();
}
