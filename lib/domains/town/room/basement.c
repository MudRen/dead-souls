#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("教堂地下室");
    SetLong("这是村庄教堂黑暗潮湿的地下室。西墙上有一扇电梯门。");
    SetItems(([
                ({"elevator","elevator door","door","wall","west wall"}) : "嵌入西墙的是一部电梯。旁边有一个按钮，大概是用来呼叫电梯的。"
                ]) );
    SetInventory(([
                "/domains/town/obj/couch" : 1,
                "/domains/town/npc/leo" : ({60, 1})
                ]));
    SetExits( ([
                "west" : "/domains/town/room/elevator",
                ]) );
    //AddStuff( ({"/domains/town/npc/leo"}) );
}
void init(){
    ::init();
    if(!present("button",this_object())) AddItem(new("/domains/town/obj/basement_button"));
}
