#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("hunting cap");
    SetId(({"hat","headgear","cap"}));
    SetAdjectives(({"soft","felt","hunting"}));
    SetShort("一顶猎帽");
    SetLong("这是一顶打猎时戴的柔软毡帽。既舒适又实用。");
    SetMass(10);
    SetBaseCost("silver",50);
    SetDamagePoints(10);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 1);
    SetProtection(BLADE, 1);
    SetProtection(KNIFE, 1);
    SetItems( ([
                ({"pheasant","feather"})  : "Looks like a pheasant feather.",
                ]) );
}

void init(){
    ::init();
}
