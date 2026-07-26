#include <lib.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("complex key");
    SetId( ({ "key", "mansion safe key" }) );
    SetAdjectives( ({ "complex", "complicated", "complicated looking" }) );
    SetShort("一把复杂的钥匙");
    SetLong("这是一把看起来很复杂的钥匙。");
    SetMass(1);
    SetBaseCost("silver",1);
    SetDisableChance(100);
}

void init(){
    ::init();
}
