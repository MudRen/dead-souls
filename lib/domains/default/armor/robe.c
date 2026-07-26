#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create(){
    ::create();
    SetKeyName("wizard robe");
    SetAdjectives( ({"wizards", "wizard's", "soft", "wizard"}) );
    SetId(({"robe","cloak","duster"}));
    SetShort("一件长袍");
    SetLong("这是一件宽大、看起来很舒适的长袍，像巫师穿的那种。它有许多口袋和隔层可以装东西。");
    SetProperties(([
                "gamma" : 3,
                "no steal" : 1,
                ]));
    SetCanClose(1);
    SetMaxCarry(5000);
    SetMass(200);
    SetBaseCost("silver",100);
    SetDamagePoints(100);
    SetArmorType(A_CLOAK);
    SetProtection(MAGIC, 10);
    SetProtection(COLD, 10);
}
void init(){
    ::init();
}
