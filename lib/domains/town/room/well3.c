#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("干涸的泉眼");
    SetLong("这个小而黑暗的房间似乎是从基岩中凿出来的，地板上钻了一个孔。考虑到挖掘这种坚硬材料的困难，这个井水系统一定耗费了一大笔财富和大量劳动力来建造。一扇门向东通往水隧道和水井。");
    SetItems(([
                ({ "hole", "floor" }) : "这个孔似乎是泉水进入的地方，用来淹没这个房间并填满东边的水井。",
                ({ "dirt", "dust" }) : "这里有很多灰尘。空井很少会在清洁日得到优先考虑。",
                ({ "bottom", "well" }) : "肮脏、发霉且令人不愉快。",
                ({ "vermin", "rats", "bugs" }) : "看起来他们此刻正在躲着你。",
                "haven" : "害虫的好地方。",
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
