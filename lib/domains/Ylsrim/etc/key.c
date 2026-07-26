/*    /domains/Ylsrim/etc/key.c
 *    from the Dead Souls Object Library
 *    created by Descartes of Borg 960512
 */

#include <lib.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("key");
    SetId( ({ "key", "special_key_id" }) );
    SetAdjectives( ({ "brilliant", "silver" }) );
    SetShort("一把银钥匙");
    SetLong("这是一把闪亮的银钥匙，没有任何标记。");
    SetMass(50);
    SetValue(15);
    SetDisableChance(90);
}

