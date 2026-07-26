#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetAmbientLight(30);
    SetClimate("indoors");
    SetShort("走廊，东段");
    SetLong("你在虚拟校区行政楼一楼的一条东西走向的走廊里。学生休息室在南边。");
    SetExits( ([ 
                "south" : "/domains/campus/room/lounge",
                "west" : "/domains/campus/room/corridor",
                "east" : "/domains/campus/room/corridor4",
                ]) );

}
void init(){
    ::init();
}
