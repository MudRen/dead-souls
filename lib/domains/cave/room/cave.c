#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(5);
    SetNightLight(15);
    SetDayLight(25);
    SetShort("一个黑暗的洞穴");
    SetNightLong("这是一个凿入河岸岩壁的洞穴。洞穴向西敞开，外面是黑夜。东边是黑暗。");
    SetDayLong("这是一个凿入河岸岩壁的洞穴。阳光从西边河流的方向照进来。东边，洞穴继续延伸向黑暗之中。");
    SetLong("这是一个靠近河岸的小洞穴。");
    SetItems(([
                ({ "wall", "rocky wall", "river bank wall", "riverbank wall", "rocky river bank wall", "rocky riverbank wall" }) : "当地的河流经过长年冲刷，在这里形成了一个狭窄陡峭的峡谷。这个洞穴就是从峡谷的岩壁中挖掘出来的。",
                ]));
    SetExits( ([
                "west" : "/domains/town/room/riverbank",
                "east" : "/domains/cave/room/cavepass1.c",
                ]) );
    SetInventory(([
                ]));
}
void init(){
    ::init();
}
