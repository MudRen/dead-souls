#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("走廊");
    SetLong("你在虚拟校区行政楼一楼的一条东西走向的走廊里。南边有一扇门，通往招生办公室。");
    SetItems( (["corridor" : "这是一条铺着地毯的走廊，向西延伸。",
                "floor" : "地毯是紫色的，颇有几分机构风格。",
                "carpet" : "地毯是紫色的，颇有几分机构风格。"]) );
    SetExits( ([ 
                "south" : "/domains/campus/room/start",
                "east" : "/domains/campus/room/corridor2",
                "west" : "/domains/campus/room/corridor3",
                ]) );
    SetProperty("no attack", 1);
    SetDoor("south", "/domains/campus/doors/plain_door");
}
int CanReceive(object ob) {
    if(ob && ob->GetRace() == "rodent"){
        message("info","You are repelled by rodenticide.",ob);
        return 0;
    }
    return ::CanReceive(ob);
}
void init(){
    ::init();
}
