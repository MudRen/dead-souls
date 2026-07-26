#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("baseball cap");
    SetAdjectives( ({"red", "old", "greasy", "dirty", "baseball", "cat"}) );
    SetId( ({"cap", "hat", "cover"}) );
    SetShort("红色棒球帽");
    SetLong("一顶油腻、破旧、肮脏的棒球帽，曾经主要是红色的，正面印着'CAT'字样。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetArmorType(A_HELMET);
}

void init(){
    ::init();
}
