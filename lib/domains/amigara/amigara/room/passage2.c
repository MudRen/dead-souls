#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    ::create();
    SetAmbientLight(5);
    SetShort("黑暗通道");
    SetLong("这是一条黑暗的地下通道。墙壁粗糙而光秃。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这里通往地下区域。",
                ({ "area", "cave like area", "cavelike area" }) : "一个在山体中开凿出来的空间。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个普通地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地开凿于地下，这些通道的墙壁暴露着地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetExits( ([
                "north" : "/domains/amigara/room/guard_room",
                "west" : "/domains/amigara/room/passage1",
                "east" : "/domains/amigara/room/passage3.c",
                ]) );

    SetInventory(([
                ]));
    SetClimate("indoors");

}
void init(){
    ::init();
}
