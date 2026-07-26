#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(5);
    SetShort("地下通道");
    SetLong("这是一条黑暗的地下通道。墙壁粗糙而裸露。西边通道通向一个类似洞穴的区域。通道从这里继续向东北和东方延伸。");
    SetItems(([
                ({ "passage", "passageway", "This provides access to areas below the ground." }) : "这条通道通往地下区域。",
                ({ "area", "cave like area", "cavelike area" }) : "西边似乎有一个类似洞穴的区域，通向外面。",
                ({ "ground", "rock", "rocks", "earth", "dirt", "stone", "stones" }) : "粗糙而肮脏，正如一个简单地下区域所应有的样子。",
                ({ "wall", "walls", "rough walls", "rough and bare walls", "bare walls", "bare and rough walls" }) : "粗糙地凿入地下，通道的墙壁露出了地下的岩石。显然这个区域的建造注重实用和效率。",
                ]));
    SetInventory(([
                "/domains/cave/npc/orc_guard5" : 1,
                ]));
    SetClimate("indoors");
    SetExits( ([
                "east" : "/domains/cave/room/cavepass2",
                "west" : "/domains/cave/room/cave",
                "northeast" : "/domains/cave/room/cavepass3.c",
                ]) );

}
void init(){
    ::init();
}
