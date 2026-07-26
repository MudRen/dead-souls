#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("uniform");
    SetAdjectives( ({"food workers","food worker's"}) );
    SetId( ({"overalls", "smock"}) );
    SetShort("餐饮工作服");
    SetLong("这是一套餐饮工作服，用来让工人的身体与食物保持适当距离。");
    SetMass(50);
    SetArmorType(A_BODY_ARMOR);
}
void init(){
    ::init();
}
