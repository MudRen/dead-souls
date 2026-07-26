#include <lib.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("key");
    SetId( ({ "key", "cavetroll key" }) );
    SetAdjectives( ({ "metal" }) );
    SetShort("一把金属钥匙");
    SetLong("这是一把金属制成的钥匙。");
    SetMass(1);
    SetBaseCost("silver",1);
    SetDisableChance(100);
}

void init(){
    ::init();
}
