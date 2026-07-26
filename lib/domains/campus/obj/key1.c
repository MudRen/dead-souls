/*    /domains/Midian/etc/key.c
 *    from the Dead Souls Object Library
 *    created by Descartes of Borg 960512
 */

#include <lib.h>

inherit LIB_ITEM;


protected void create() {
    item::create();
    SetKeyName("key");
    SetId(({"key","locker_key_1"}));
    SetAdjectives(({"locker","small",}));
    SetShort("小钥匙");
    SetLong("这是一把小钥匙，也许是挂锁或储物柜的。");
    SetMass(1);
    SetDollarCost(2);
    SetDisableChance(90);
}
void init(){
    ::init();
}
