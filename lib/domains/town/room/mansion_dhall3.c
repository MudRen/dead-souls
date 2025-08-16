#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆一楼走廊南端");
    SetLong("你在公馆装饰精美的一楼走廊里。"
            "东边和西边都有房间，走廊"
            "向北延伸。一个大型"
            "圆形大理石楼梯通向"
            "二楼。");
    SetItems( ([
                "hallway" : "一个通往房子其他地方的内部区域。",
                ({"mansion","house"}) : "你在一座美丽的公馆里。",
                ({"stairs","staircase"}) : "一系列精美雕刻的"
                "向上螺旋到二楼的台阶。它是用大理石雕刻而成。"
                ]) );
    SetExits( ([ 
                "north" : "/domains/town/room/mansion_dhall2",
                "west" : "/domains/town/room/mansion_room8",
                "up" : "/domains/town/room/mansion_uhall3",
                ]) );

}
void init(){
    ::init();
}
