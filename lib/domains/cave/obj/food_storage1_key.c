#include <lib.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("key");
    SetId( ({ "food_storage_one","key for a door" }) );
    SetAdjectives( ({ "simple","iron","door" }) );
    SetShort("一把铁钥匙");
    SetLong("这是一把简单的铁门钥匙。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetDisableChance(1);
}

void init(){
    ::init();
}
