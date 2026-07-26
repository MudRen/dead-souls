#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

int readSign() {
    this_player()->more("/domains/town/txt/warning_sign.txt");
    return 1;
}
protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetObviousExits("north, south");
    SetShort("南旧萨奎沃尔路");
    SetLong("这是一条鹅卵石道路，向南通往某个大学校园。");
    SetItems( ([
                ({"road","cobblestone road"}) : "一条鹅卵石道路，向南延伸。",
                //"sign":"A large sign on the road. To read it, 'read sign'.",
                ({"grate","drainage grate","sewer","sewer grate"}) : "一个似乎通往下水道的格栅。从这里无法打开。",
                ]) );
    //SetSkyDomain("town");
    AddTerrainType(T_ROAD);
    SetExits( ([
                "south" : "/domains/campus/room/npath2.c",
                ]) );
    if(file_exists("/domains/campus/doors/grate.c")){
        AddExit("down", "/domains/campus/room/sewer3");
        SetDoor("down","/domains/campus/doors/grate");
    }
    if(strsrch(mud_name(), "Dead Souls")){
        //AddExit("north", "/domains/town/room/south_road1");
    }
    SetInventory(([
                ]));
    //SetRead("sign", (: readSign :) );
    //AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    ::init();
}
