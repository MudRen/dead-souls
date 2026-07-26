#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("走廊");
    SetLong("你在虚拟校区行政楼一楼的一条东西走向的走廊里。大楼的快餐吧在北边，南边的门通往楼梯间。门厅和大楼出口在西边。");
    SetItems( (["corridor" : "这是一条铺着地毯的走廊，向西延伸。",
                "floor" : "地毯是紫色的，颇有几分机构风格。",
                "carpet" : "地毯是紫色的，颇有几分机构风格。"]) );
    SetExits( ([
                "south" : "/domains/campus/room/stairwell",
                "east" : "/domains/campus/room/corridor",
                "west" : "/domains/campus/room/foyer",
                "north" : "/domains/campus/room/snack.c",
                ]) );
    SetDoor("south","/domains/campus/doors/top_stairs");
    SetProperty("no attack", 1);
}
int CanReceive(object ob){
    if(ob && ob->GetRace() == "rodent"){
        message("info","You are repelled by rodenticide.",ob);
        return 0;
    }
    return ::CanReceive(ob);
}
void init(){
    ::init();
}
