#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("slug");
    SetId( ({"slug","round","bullet","projectile"}) );
    SetAdjectives( ({"spent","lead"}) );
    SetShort("用过的弹头");
    SetLong("这块扭曲的小金属似乎是用过的弹头：从枪中射出并进入目标的那部分子弹。它的形状因撞击目标而变形。");
    SetMass(1);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
