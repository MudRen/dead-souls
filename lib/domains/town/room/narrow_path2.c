#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("狭窄小径");
    SetLong("这是一条穿过茂密森林的狭窄小径，南北走向。厚厚的植被使得离开小径的旅行变得不可能。");
    SetItems(([
                ({ "path", "trail" }) : "一条非常狭窄的小径，似乎被周围隐约的树林所威胁。很难想象是什么力量在这片植被中切出了这条细长的路径。",
                ({ "forest", "wood", "vegetation" }) : "周围都是生长得极其茂密的植被，不可能离开小径闲逛。",
                ]));
    SetSkyDomain("town");
    SetExits( ([
                "north" : "/domains/town/room/narrow_path",
                "south" : "/domains/town/room/cratshack.c",
                ]) );

    SetInventory(([
                ]));

}
void init(){
    ::init();
}

int CanReceive(object ob){
    if(answers_to("provost",ob)) return 0;
    return ::CanReceive();
}
