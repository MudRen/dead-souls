#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("wizard's hat");
    SetAdjectives( ({"wizard","wizards", "floppy", "large", "conical", "blue"}) );
    SetId( ({"hat"}) );
    SetShort("巫师帽");
    SetLong("这是一顶宽大的软帽，四周有宽帽檐，中间是圆锥形。帽子是深蓝色的，上面装饰着黄色的月亮和星星图案。");
    SetProperties(([
                "beta" : 2,
                ]));
    SetMass(50);
    SetBaseCost("silver",500);
    SetDamagePoints(100);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
}
void init(){
    ::init();
}
