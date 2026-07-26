#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("chest");
    SetId(({"chest","wooden chest"}));
    SetShort("一个木箱");
    SetLong("这是一个坚固的木箱，用于存放贵重物品。\n"+
            "这是一个不透明容器的示例。");
    SetInventory(([
                "/domains/town/armor/collar" : 1,
                "/domains/default/armor/breather" : 1,
                "/domains/default/armor/badge" : 1,
                "/domains/default/armor/wizard_hat" : 1,
                "/domains/default/obj/manual" : 1,
                "/secure/obj/machine" : 1,
                "/domains/default/obj/gps" : 1,
                "/domains/default/armor/robe" : 1,
                "/domains/default/obj/meter" : 1,
                "/secure/obj/control" : 1,
                "/secure/obj/memo" : 1,
                "/secure/obj/staff" : 1,
                "/domains/default/obj/pinger" : 1,
                "/secure/obj/medtric" : 1,
                "/secure/obj/glasses" : 1,
                "/domains/default/armor/jade_ring" : 1,
                "/domains/default/armor/gray_amulet" : 1,
                ]));
    SetMass(2000);
    SetBaseCost(50);
    SetMaxCarry(10000);
    SetCanClose(1);
    SetClosed(1);
    SetPreventGet("The chest does not budge.");
}

void init(){
    ::init();
}
