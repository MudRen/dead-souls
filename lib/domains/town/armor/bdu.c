#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("battle dress uniform");
    SetId(({"uniform","bdu","bdu's","fatigues"}));
    SetAdjectives(({"camouflage","battle","dress","combat"}));
    SetShort("一套作战服");
    SetLong("这套制服由一件迷彩上衣和一条迷彩裤组成，是军队标准制式装备。");
    SetMass(10);
    SetBaseCost("silver",100);
    SetDamagePoints(100);
    SetArmorType(A_BODY_ARMOR);
}

void init(){
    ::init();
}
