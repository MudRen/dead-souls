#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
void create(){
    ::create();
    SetKeyName("slug");
    SetId( ({"slug","round","bullet","projectile"}) );
    SetAdjectives( ({"spent","lead"}) );
    SetShort("一颗用过的弹头");
    SetLong("这块扭曲的小金属块看起来是一颗用过的子弹头。");
    SetMass(1);
    SetBaseCost("silver",0);
    SetVendorType(VT_TREASURE);
}
