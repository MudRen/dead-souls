#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("狭窄小径");
    SetLong("这是从东北通向绿色山谷的一条狭窄小径，向南穿过茂密的森林。厚厚的植被使离开小径的旅行变得不可能。");
    SetItems(([
                ({ "path", "trail" }) : "一条非常狭窄的小径，似乎被周围隐约的树林所威胁。很难想象是什么力量在这片植被中切出了这条细长的路径。",
                ({ "forest", "wood", "vegetation" }) : "周围都是生长得极其茂密的植被，不可能离开小径闲逛。"
                ]));
    SetSkyDomain("town");
    SetExits( ([
                "northeast" : "/domains/town/room/valley",
                "south" : "/domains/town/room/narrow_path2.c",
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
