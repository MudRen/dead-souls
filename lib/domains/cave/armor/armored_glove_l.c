#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("armored glove");
    SetAdjectives( ({"armored", "orc", "orcish", "protective"}) );
    SetId(({"glove","left glove"}));
    SetShort("一只装甲手套");
    SetLong("这是一只兽人设计的装甲手套，设计用来覆盖左手和左臂，看起来极其耐用且防护性强。");
    SetMass(60);
    SetBaseCost("silver", 300);
    SetProtection(BLUNT,15);
    SetProtection(BLADE,15);
    SetProtection(KNIFE,15);
    SetArmorType(A_LONG_GLOVE);
    SetFingers(6);
    SetRestrictLimbs(({"left hand","left arm"}));
}

void init(){
    ::init();
}
