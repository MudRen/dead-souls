#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("狭窄小径");
    SetLong("这是一条南北向穿过茂密森林的狭窄小径。茂密的植被使得偏离小径变得不可能。");
    SetItems(([
                ({ "path", "trail" }) : "一条非常狭窄的小径，四周似乎受到迫近的树林威胁。很难想象是什么力量在这里的植被中开辟出这条小径。",
                ({ "forest", "wood", "vegetation" }) : "四周的植被生长得异常茂密，让人无法偏离小路。",
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
