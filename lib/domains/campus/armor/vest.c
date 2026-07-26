#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("paisley vest");
    SetId(({"vest"}));
    SetAdjectives(({"paisley","colorful","hippie","hippy","psychedelic"}));
    SetShort("彩色佩斯利花纹背心");
    SetLong("一件看起来很蠢的嬉皮士背心，上面印着迷幻的佩斯利花纹。");
    SetMass(5);
    SetDollarCost(1);
    SetDamagePoints(1);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_VEST);
}
