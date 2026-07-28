#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("chest");
    SetId(({"chest","wooden chest"}));
    SetShort("一个木箱");
    SetLong("这是一个结实的木箱，用于存放贵重物品。");
    SetMass(500);
    SetBaseCost("silver",50);
    SetMaxCarry(500);
    SetPreventPut("你不能把这个放进去！");
    SetInventory(([
                "/domains/town/obj/gcoinbag" : 1,
                "/domains/town/obj/maglite" : 1,
                "/domains/town/obj/m_key" : 1,
                ]));
    SetCanClose(1);
    SetClosed(1);
}

void init(){
    ::init();
}

mixed CanGet(object ob) { return "箱子纹丝不动。";}
