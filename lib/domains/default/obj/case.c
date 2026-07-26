#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("case");
    SetId( ({ "case" }) );
    SetAdjectives( ({ "mounted","wall","glass", "display" }) );
    SetShort("一个玻璃展示柜");
    SetLong("这是一个 designed to contain and display firearms 的玻璃柜。");
    SetInventory(([
                "/domains/default/weap/m16rifle" : 1,
                "/domains/default/weap/9mil" : 1,
                "/domains/default/weap/357pistol" : 1,
                "/domains/default/weap/prifle" : 1,
                ]));
    SetOpacity(0);
    SetCanClose(1);
    SetClosed(1);
    SetMass(274);
    SetBaseCost("silver",1);
    SetMaxCarry(1500);
}
void init(){
    ::init();
}

int CanReceive(object ob) {
    if(!inherits(LIB_FIREARM,ob)) {
        write("这是一个仅用于 firearms 的柜子。");
        return 0;
    }
    else return 1;
}

mixed CanGet(object ob) { return "这个柜子纹丝不动。";}
