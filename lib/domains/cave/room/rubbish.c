#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(0);
    SetShort("地下垃圾场");
    SetLong("这个地下区域到处都是腐烂发臭的垃圾和生物废物。一条通道从这里通向西边。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetInventory(([
                "/domains/cave/obj/garbage" : 13,
                "/domains/cave/npc/rat" : 18,
                "/domains/cave/obj/waste" : 37,
                ]));
    SetClimate("indoors");
    SetExits(([
                "west" : "/domains/cave/room/cavepass2",
                ]));

}
void init(){
    ::init();
}
