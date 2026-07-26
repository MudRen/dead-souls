#include <lib.h>
#include ROOMS_H
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("走廊");
    SetLong("你在虚拟校区行政楼一楼的一条东西走向的走廊里。北边是校园书店，南边有一间会议室。");
    SetItems( (["corridor" : "这是一条铺着地毯的东西走向走廊。",
                "floor" : "地毯是紫色的，颇有几分机构风格。",
                "carpet" : "地毯是紫色的，颇有几分机构风格。"]) );
    SetExits( ([
                "south" : "/domains/campus/room/conf",
                "north" : "/domains/campus/room/bookstore",
                "west" : "/domains/campus/room/corridor2.c",
                ]) );
    SetProperty("no attack", 1);
}
int CanReceive(object ob){
    if(ob && ob->GetRace() == "rodent"){
        message("info","You are repelled by rodenticide.",ob);
        if(!environment(ob) && interactive(ob)) ob->eventMove(ROOM_START);
        return 0;
    }
    return ::CanReceive(ob);
}
void init(){
    ::init();
}
