#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(40);
    SetNightLight(10);
    SetDayLight(30);
    SetShort("森林空地");
    SetLong("这是森林中一条小径上的空地。小径向西通向一个小山谷，向东北通向森林和一座桥。");
    SetItems( ([
                "clearing" : "一个树木稀少的区域。","
                "path" : "这条森林小径东西走向。北边有一条小径。","
                ({"forest","wood","woods"}) : "这是一个"黑暗、令人毛骨悚然的森林。你站在空地上的小径上，所以这里稍微亮一些。","
                ({ "small trail","trail"}) : "一条通向北方森林深处的小径。","
                "valley" : "西边有一个山谷。","
                "town" : "东边远处的一个小镇。""
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
