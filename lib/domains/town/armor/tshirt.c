#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("a Def Leppard shirt");
    SetId(({"shirt","def leppard shirt"}));
    SetAdjectives(({"Def Leppard", "def leppard", "stupid", "black"}));
    SetShort("一件Def Leppard乐队T恤");
    SetLong("一件看起来很蠢的黑色衬衫，上面印着一个荒谬的乐队标志。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_SHIRT);
    //SetRestrictLimbs(({"torso"}));
}

void init(){
    ::init();
}
