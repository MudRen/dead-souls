#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("safe");
    SetId(({"safe"}));
    SetAdjectives(({"metal","small"}));
    SetShort("一个金属保险箱");
    SetLong("这是一个小保险箱，大约2英尺高，可以存放贵重物品。");
    SetMaxCarry(1000);
    SetInventory(([
                "/domains/campus/weap/grenade" : 1,
                "/domains/town/weap/9mil" : 1,
                "/domains/town/obj/slip_heal" : 4,
                ]));
    SetMass(1000);
    SetBaseCost("silver",50);
    SetCanClose(1);
    SetClosed(1);
    SetCanLock(1);
    SetLocked(1);
    SetLockStrength(80);
    SetKey("mansion safe key");
    AddMoney("silver",1000);
}

mixed CanGet(object ob) { return "保险箱固定在地上，搬不动。";}
void init(){
    ::init();
}
