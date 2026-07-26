#include <lib.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("key");
    SetId( ({ "key", "mansion key" }) );
    SetAdjectives( ({ "brilliant", "silver" }) );
    SetShort("一把银钥匙");
    SetLong("这是一把没有标记的闪亮银钥匙。");
    SetMass(1);
    SetBaseCost("silver",1);
    SetDisableChance(100);
}

void init(){
    ::init();
}
