#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(0);
    SetShort("地下通道");
    SetLong("这是一条黑暗的地下通道。墙壁粗糙而裸露。通道从这里向西南和西北延伸。北边、西边和南边都有房间。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetExits( ([
                "south" : "/domains/cave/room/chieftain",
                "west" : "/domains/cave/room/dining1",
                "northwest" : "/domains/cave/room/cavepass8",
                "southwest" : "/domains/cave/room/cavepass12",
                "north" : "/domains/cave/room/shop.c",
                ]) );
    SetClimate("indoors");

    SetInventory(([
                ]));
}
void init(){
    ::init();
}
