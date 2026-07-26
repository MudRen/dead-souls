#include <lib.h>

#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create() {
    ::create();
    SetKeyName("backpack");
    SetId(({"pack"}));
    SetAdjectives(({"leather","soft","brown"}));
    SetShort("一个棕色软皮背包");
    SetLong("这是一个中等大小的背包，由柔软的棕色皮革制成。可以装很多东西。");
    SetMass(100);
    SetBaseCost("silver",30);
    SetCanClose(1);
    SetClosed(1);
    SetMaxCarry(500);
    SetArmorType(A_CLOAK);
}

void init(){
    ::init();
}
