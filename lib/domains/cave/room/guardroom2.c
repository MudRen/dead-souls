#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(0);
    SetShort("地下房间");
    SetLong("这是一间黑暗的地下房间。墙壁粗糙而裸露。一条通道通向南边。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetInventory(([
                "/domains/cave/obj/tall_lamp" : 1,
                "/domains/cave/npc/orc_guard4" : 2,
                "/domains/cave/npc/orc_guard3" : 3,
                ]));
    SetExits( ([
                "south" : "/domains/cave/room/cavepass7",
                "north" : "/domains/cave/room/kurogane.c",
                ]) );
    SetClimate("indoors");

    SetDoor("north", "/domains/cave/doors/kurogane.c");

}
void init(){
    ::init();
}
