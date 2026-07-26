#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园东客房");
    SetLong("你在庄园楼上的东客房里。房间装饰和家具都很豪华。床的状态表明最近有人在这里住过。");
    SetItems( ([
                ({"furniture","furnishings"}) : "舒适而美观。"
                ]) );
    SetExits( ([
                "west" : "/domains/town/room/mansion_uhall1"
                ]) );
    SetInventory(([
                "/domains/town/obj/obag" :1,
                "/domains/town/obj/gbed" :1,
                "/domains/town/armor/boot_l" :1,
                "/domains/town/armor/boot_r" :1,
                ]) );

    SetDoor("west", "/domains/town/doors/m1.c");

}
void init(){
    ::init();
}
