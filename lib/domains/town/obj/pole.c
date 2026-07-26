/*    /domains/Ylsrim/etc/pole.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951009
 */

#include <lib.h>
#include <vendor_types.h>

inherit LIB_POLE;
inherit LIB_ITEM;

protected void create() {
    pole::create();
    item::create();
    SetKeyName("bamboo pole");
    SetId( ({ "pole", "bamboo pole", "fishing pole"  }) );
    SetAdjectives( ({ "bamboo", "feeble" }) );
    SetShort("一根竹竿");
    SetLong("这是一根脆弱的竹竿，末端系着一根线。可以用它来钓鱼。");
    SetClass(1);
    SetValue(10);
    SetMass(30);
    SetVendorType(VT_TREASURE | VT_FISHING);
    SetStrength(200);
    SetChance(20);
}

protected mixed AddSave(mixed *var) {
    return item::AddSave(var);
}
