#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create(){
    ::create();
    SetKeyName("overalls");
    SetId(({"overalls","pants", "trousers"}));
    SetAdjectives(({"worn","abused","pair of","set of"}));
    SetShort("一条工装裤");
    SetLong("这是一条破旧磨损的工装裤，带有大口袋可以装东西。");
    SetMass(50);
    SetMaxCarry(300);
    SetBaseCost("silver",1);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_CUSTOM);
    SetInventory( ([ 
                "/domains/campus/weap/knife" : 1,
                ]) );
    SetRestrictLimbs( ({ "right leg","left leg","torso" }) );
}

void init(){
    ::init();
}
