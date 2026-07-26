#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("前廊");
    SetLong("这是一座老房子摇摇欲坠的前廊。前门在南边。北边是树林中的一片空地，以及一条通往远方的小路。");
    SetItems(([
                ({ "forest", "wood", "vegetation" }) : "四周的植被生长得异常茂密，让人无法偏离小路。",
                ({ "porch", "front porch" }) : "一座白色旧房子的木质前廊。",
                ({ "trail", "path" }) : "北边有一条狭窄的小路通向树林。",
                ({ "clearing", "woods" }) : "仿佛有某种强大的魔法，树林在这里变得开阔，房子就矗立于此。",
                ({ "house", "white house", "old house" }) : "这座房子看起来饱经风霜、年久失修，相当老旧。它的建筑风格已经过时。尽管外表破旧，这座房子似乎有一种静谧的尊严，仿佛多年来许多人曾是它的朋友，而它只是在等待他们的归来。",
                ]));
    SetInventory(([
                "/domains/town/obj/rocking_chair" : 2,
                ]));
    SetExits( ([
                "north" : "/domains/town/room/cratshack",
                "south" : "/domains/town/room/living_room.c",
                ]) );

    SetDoor("south", "/domains/town/doors/house_door.c");

}
void init(){
    ::init();
}
int CanReceive(object ob){
    if(answers_to("provost",ob)) return 0;
    return ::CanReceive();
}
