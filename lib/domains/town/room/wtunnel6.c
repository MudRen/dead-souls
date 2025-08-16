#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("黑暗隧道");
    SetLong("这条隧道有非常光滑的石墙，向南延伸。还有一个东北方向的出口。");
    SetItems(([
                ({ "hole", "holes", "floor" }) : "这些孔洞似乎是泉水进入的地方，用来淹没这个房间并填满东边的水井。",
                ({ "dirt", "dust" }) : "这里有很多灰尘。空井很少会在清洁日得到优先考虑。",
                ({ "bottom", "well" }) : "肮脏、发霉且令人不愉快。",
                ({ "vermin", "rats", "bugs" }) : "看起来他们此刻正在躲着你。",
                "haven" : "害虫的好地方。",
                ({ "rock", "bedrock" }) : "这是地下深处致密坚硬的岩石。",
                ]));
    SetFlowLimit(3);
    SetExits( ([
                "south" : "/domains/town/room/wtunnel5",
                "northeast" : "/domains/cave/room/cavetroll.c",
                ]) );

    SetDoor("northeast", "/domains/town/doors/gate.c");

}
void init(){
    ::init();
}
