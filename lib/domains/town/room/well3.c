#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("干涸泉眼");
    SetLong("这个狭小黑暗的房间似乎是从基岩中开凿出来的，地板上钻有一个洞。考虑到在如此坚硬的物质中挖掘的难度，这套井水系统一定花费了大量金钱和人力来建造。一扇门向东通往水道隧道和水井。");
    SetItems(([
                ({ "hole", "floor" }) : "这个洞似乎是泉水流入并注满东边水井的入口。",
                ({ "dirt", "dust" }) : "这里到处都是灰尘。废弃的水井在清洁日很少受到重视。",
                ({ "bottom", "well" }) : "肮脏、发霉、令人不快。",
                ({ "vermin", "rats", "bugs" }) : "看起来它们现在正躲着你。",
                "haven" : "害虫的好去处。",
                ({ "rock", "bedrock" }) : "这是地下深处致密坚硬的岩石。",
                ]));
    SetFlowLimit(3);
    SetExits( ([
                "east" : "/domains/town/room/well2",
                "down" : "/domains/town/room/source.c",
                ]) );
    SetDoor("east", "/domains/town/doors/welldoor2.c");

    SetDoor("down", "/domains/town/doors/grate.c");

}
void init(){
    ::init();
}
