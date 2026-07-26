#include <lib.h>
#include <terrain_types.h>
#include <medium.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    ::create();
    SetAmbientLight(5);
    SetShort("洞穴半空中");
    SetLong("这是城镇森林北面石山中的一个洞穴。这里没有地面。下方是一片黑暗。");
    SetItems(([
                ({ "wall", "rocky wall", "mountain wall", "rough stone mountain wall", "stone mountain wall" }) : "地质活动在漫长岁月中形成了这个洞穴，但显然有智慧生物将其改造成了适合居住的大小和形状。",
                ]));
    SetExits( ([
                "south" : "/domains/amigara/room/cave",
                "down" : "/domains/amigara/room/passage1.c",
                ]) );

    SetInventory(([
                ]));
    SetClimate("indoors");
    SetTerrainType(T_MIDAIR);
    SetMedium(MEDIUM_AIR);
}
void init(){
    ::init();
}
