#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("paisley vest");
    SetId(({"vest"}));
    SetAdjectives(({"goofy","goofy-looking", "goofy looking", "paisley","colorful","hippie","hippy","psychedelic"}));
    SetShort("一件彩色佩斯利花纹背心");
    SetLong("一件看起来傻傻的嬉皮士背心，上面有迷幻的佩斯利花纹。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_VEST);
}

void init(){
    ::init();
}
