#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("smock");
    SetAdjectives( ({"bar workers","food worker's"}) );
    SetId( ({"overalls", "smock", "simple"}) );
    SetShort("一件简单的工作服");
    SetLong("这是一套食品工人穿的工作服，用来让身体和食物保持安全距离。");
    SetMass(50);
    SetArmorType(A_BODY_ARMOR);
}

void init(){
    ::init();
}
