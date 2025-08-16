#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆一楼走廊");
    SetLong("你在公馆装饰精美的一楼走廊里。"
            "东边和西边都有房间，走廊"
            "向南延伸。北边是入口门厅。");
    SetItems( ([ 
                "hallway" : "一个通往房子其他地方的内部区域。",
                ({"mansion","house"}) : "你在一座美丽的公馆里。" ,
                "foyer" : "公馆的入口区域在北边。"
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/mansion_int",
                "south" : "/domains/town/room/mansion_dhall3",
                "west" : "/domains/town/room/mansion_room10",
                "east" : "/domains/town/room/mansion_room7.c",
                ]) );

}
void init(){
    ::init();
}
