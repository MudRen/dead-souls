#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(0);
    SetShort("地下通道");
    SetLong("这是一条黑暗的地下通道。墙壁粗糙而裸露。通道从这里向东南延伸。南边、东北和西北都有房间。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetClimate("indoors");
    SetExits( ([
                "south" : "/domains/cave/room/dining1",
                "northeast" : "/domains/cave/room/guardroom3",
                "southeast" : "/domains/cave/room/cavepass9",
                "northwest" : "/domains/cave/room/guardroom4.c",
                ]) );

    SetInventory(([
                ]));
}
void init(){
    ::init();
}
