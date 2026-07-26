#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园楼下走廊南端");
    SetLong("你在庄园装饰精美的楼下走廊里。东西两侧都有房间，走廊继续向北延伸。一座大型圆形大理石楼梯通往二楼。");
    SetItems( ([
                "hallway" : "通往房屋其他地方的室内通道。",
                ({"mansion","house"}) : "你身处一座美丽的庄园之中。",
                ({"stairs","staircase"}) : "一系列精雕细琢的台阶螺旋向上通往二楼。由大理石雕刻而成。"
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
