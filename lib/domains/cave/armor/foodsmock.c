#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("uniform");
    SetAdjectives( ({"food workers","food worker's"}) );
    SetId( ({"overalls", "smock"}) );
    SetShort("一件食品工人制服");
    SetLong("这是一套食品工人穿的工作服，用来保持身体与食物之间的卫生距离。");
    SetMass(50);
    SetArmorType(A_BODY_ARMOR);
}
void init(){
    ::init();
}
