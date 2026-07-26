#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>
#include <modules.h>

inherit LIB_ITEM;
inherit MODULES_ARMOR;
inherit MODULES_CREATE;
inherit MODULES_MAPPING;
inherit MODULES_GENERIC;
inherit MODULES_ROOM;
inherit MODULES_FILE;
inherit MODULES_MONEY;
inherit MODULES_READ;
inherit MODULES_DOOR;

protected void create(){
    item::create();
    SetKeyName("staff");
    SetId( ({ "staff", "stick", "tanstaafl"  }) );
    SetAdjectives( ({ "wood","wooden","creator","creator's","creation" }) );
    SetShort("木制法杖");
    SetLong("这根法杖古老、风化、凹凸不平。然而，它感觉相当坚固和结实。"+
            "更多信息：help staff");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetDamagePoints(50);
    SetClass(100);
    SetMass(100);
    SetNoCondition(1);
    SetWeaponType("blunt");
    SetHands(2);
    SetDamageType(BLUNT);
}
void init(){
    ::init();
}

int CanSell(object arg) { return 0; }
