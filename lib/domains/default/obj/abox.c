#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("ammunition box");
    SetId(({"can","box"}));
    SetAdjectives(({"metal","ammo","ammunition","large"}));
    SetShort("一个弹药箱");
    SetLong("这是一个 large metal box containing various kinds of ammunition。");
    SetMass(200);
    SetDollarCost(50);
    SetMaxCarry(500);
    SetCanClose(1);
    SetClosed(0);
    SetInventory( ([
                "/domains/default/obj/9mmclip": ({ 60, 2 }),
                "/domains/default/obj/223clip": ({ 60, 2 }),
                "/domains/default/weap/grenade": 3,
                ]) );
    SetPreventGet("这个金属弹药箱纹丝不动。");
}

void init(){
    ::init();
}
