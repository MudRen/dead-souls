#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆东客房");
你在公馆的楼上东客房里。房间布置豪华，家具精美。床的状态表明有人最近在这里住过。
    SetItems( ([
                ({"furniture","furnishings"}) : "舒适而吸引人。
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
