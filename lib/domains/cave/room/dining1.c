#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(0);
    SetShort("军营食堂");
    SetLong("这是一间墙壁粗糙的黑暗地下房间，布置得可以容纳想吃喝的人员。通道从这里通向北、东和南。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetInventory(([
                "/domains/cave/obj/tall_lamp" : 1,
                "/domains/cave/obj/chair" : 6,
                "/domains/cave/obj/table2" : 3,
                "/domains/cave/obj/rack" : 1,
                "/domains/cave/obj/lister" : 1,
                "/domains/cave/obj/cask5" : 1,
                "/domains/cave/npc/rybak" : 1,
                ]));
    SetClimate("indoors");
    SetExits( ([
                "south" : "/domains/cave/room/cavepass12",
                "east" : "/domains/cave/room/cavepass9",
                "north" : "/domains/cave/room/cavepass8.c",
                ]) );

}
void init(){
    ::init();
}
