#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(25);
    SetShort("园丁小屋");
    SetLong("这是花园看守者的黑暗木制小屋。从灰尘和锈迹来看，显然最近没有人在这里做太多园艺工作。");
    SetExits( ([
                "south" : "/domains/town/room/garden",
                "out" : "/domains/town/room/garden.c",
                ]) );
    SetInventory(([
                "/domains/town/obj/rayovac" : 1,
                "/domains/town/obj/ladder" : 1,
                ]) );

}
void init(){
    ::init();
}
