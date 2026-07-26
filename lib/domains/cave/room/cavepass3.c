#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(0);
    SetShort("地下通道");
    SetLong("这是一条黑暗的地下通道。墙壁粗糙而裸露。通道继续向西北和西南延伸。东北方向有某种房间。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetClimate("indoors");
    SetExits( ([
                "northwest" : "/domains/cave/room/cavepass4",
                "southwest" : "/domains/cave/room/cavepass1",
                "northeast" : "/domains/cave/room/guardroom1.c",
                ]) );

    SetInventory(([
                ]));
}
void init(){
    ::init();
}
