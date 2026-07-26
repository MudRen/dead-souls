#include <lib.h>
inherit LIB_ROOM;


int readSign() {
    this_player()->more("/domains/campus/txt/warning.txt");
    return 1;
}
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("门厅");
    SetLong("这里是虚拟校区行政楼主走廊的西端。走廊向东延伸。西边是大楼出口，通往外面的世界。\n%^GREEN%^墙上有一块大告示牌，你可以阅读。%^RESET%^");
    SetExits( ([
                "west" : "/domains/campus/room/usquare",
                "east" : "/domains/campus/room/corridor3"
                ]) );
    SetItems( (["corridor" : "这是一条铺着地毯的走廊，向西延伸。",
                "floor" : "地毯是紫色的，颇有几分机构风格。",
                "sign":"墙上的一块大告示牌。输入 'read sign' 来阅读。",
                "carpet" : "地毯是紫色的，颇有几分机构风格。"]) );
    SetRead("sign", (: readSign :) );
    SetProperty("no attack", 1);
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
