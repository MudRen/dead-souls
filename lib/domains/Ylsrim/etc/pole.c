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
    SetId( ({ "pole", "bamboo pole", "stick"  }) );
    SetAdjectives( ({ "bamboo", "feeble" }) );
    SetShort("一根竹竿");
    SetLong("这是一根纤细的竹竿，末端系着一根线。");
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
