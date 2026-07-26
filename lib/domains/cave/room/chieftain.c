#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(0);
    SetShort("地下房间");
    SetLong("这是一间黑暗的地下房间。墙壁粗糙而裸露。通道通向南和北。");
    SetItems(([
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "room", "here", "area" }) : "粗糙地凿入地下，这个区域的墙壁露出了地下的岩石。",
                ]));
    SetInventory(([
                "/domains/cave/obj/tall_lamp" : 1,
                "/domains/cave/obj/lever" : 1,
                "/domains/cave/obj/chest2" : 1,
                "/domains/cave/npc/chieftain" : 1,
                ]));
    SetExits( ([ 
                "north" : "/domains/cave/room/cavepass9",
                "south" : "/domains/cave/room/cavepass13",
                ]) );
    SetClimate("indoors");

}
void init(){
    ::init();
}
