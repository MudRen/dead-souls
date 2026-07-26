#include <lib.h>

inherit LIB_ITEM;


protected void create() {
    item::create();
    SetKeyName("key");
    SetId( ({ "key", "sample key" }) );
    SetAdjectives( ({ "simple","sample" }) );
    SetShort("一把示例钥匙");
    SetLong("这是一把简单的示例钥匙，没有任何标记。");
    SetMass(50);
    SetBaseCost(1);
    SetDisableChance(100);
}
void init(){
    ::init();
}
