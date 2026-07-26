#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(40);
    SetNightLight(10);
    SetDayLight(30);
    SetShort("林中空地");
    SetLong("这是森林小径上的一片小空地。小径向西通往一个小山谷，东北方向通往一片森林和一座桥。");
    SetItems( ([
                "clearing" : "一片树木稀少的区域。",
                "path" : "这条森林小径东西走向。北边有一条小径。",
                ({"forest","wood","woods"}) : "这是一片阴暗、令人毛骨悚然的森林。你站在空地中的小径上，所以这里稍微明亮一些。",
                ({ "small trail","trail"}) : "一条通往北方森林深处的小径。",
                "valley" : "西边有一个山谷。",
                "town" : "东方远处有一座城镇。"
                ]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "northeast" : "/domains/town/room/forest_path1",
                "west" : "/domains/town/room/valley",
                ]) );
}
void init(){
    ::init();
}
