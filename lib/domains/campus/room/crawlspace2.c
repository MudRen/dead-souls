#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("狭小的爬行空间");
    SetLong("你在地下室楼梯下方一个狭小的空间里。这里黑暗、拥挤、肮脏。");
    SetItems(([
                ({"crawlspace","space"}) : "你在楼梯下方的空间里。",
                "basement" : "地下室就在爬行空间外面。",
                "stairs" : "你在楼梯下面。"]));
    SetExits( ([ 
                "out" : "/domains/campus/room/stairwell2d"
                ]) );
    SetInventory(([
                ]));
}
void reset(){
    ::reset();
}
