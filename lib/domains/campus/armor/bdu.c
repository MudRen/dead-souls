#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("battle dress uniform");
    SetId(({"uniform","bdu","bdu's","fatigues"}));
    SetAdjectives(({"camouflage","battle","dress","combat"}));
    SetShort("作战服");
    SetLong("这套制服由一件迷彩上衣和一条迷彩裤组成。绿色底色上有棕色和黑色的斑驳迷彩图案，在树林环境中应该能提供良好的隐蔽效果。");
    SetMass(10);
    SetDollarCost(100);
    SetDamagePoints(100);
    SetArmorType(A_BODY_ARMOR);
}
