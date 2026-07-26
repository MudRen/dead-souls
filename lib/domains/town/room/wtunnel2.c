#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("黑暗隧道");
    SetLong("这条隧道的石壁非常光滑，东西走向。");
    SetItems(([
                ({ "hole", "holes", "floor" }) : "这些洞似乎是泉水流入并注满东边水井的入口。",
                ({ "dirt", "dust" }) : "这里到处都是灰尘。废弃的水井在清洁日很少受到重视。",
                ({ "bottom", "well" }) : "肮脏、发霉、令人不快。",
                ({ "vermin", "rats", "bugs" }) : "看起来它们现在正躲着你。",
                "haven" : "害虫的好去处。",
                ({ "rock", "bedrock" }) : "这是地下深处致密坚硬的岩石。",
                ]));
    SetFlowLimit(3);
    SetExits( ([
                "west" : "/domains/town/room/source",
                "east" : "/domains/town/room/wtunnel3.c",
                ]) );

    SetDoor("east", "/domains/town/doors/pressure_door.c");

}
void init(){
    ::init();
}
