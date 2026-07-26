#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("shirt");
    SetAdjectives( ({"horse", "t", "simple", "cotton"}) );
    SetId( ({"tshirt", "t-shirt"}) );
    SetShort("一件衬衫");
    SetLong("一件简单的棉衬衫，上面画着一匹马，标语是：'我是小马女孩！'");
    SetMass(5);
    SetBaseCost("silver",1);
    SetArmorType(A_SHIRT);
}

void init(){
    ::init();
}
