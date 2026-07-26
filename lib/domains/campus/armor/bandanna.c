#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("bandanna");
    SetAdjectives( ({"red"}) );
    SetId( ({"kerchief", "handkerchief"}) );
    SetShort("红色头巾");
    SetLong("这是一条红色头巾，被改造成简易头饰，可能是为了防止头发沾上灰尘，同时也避免灰尘掉落。");
    SetMass(1);
    SetBaseCost("silver",1);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 1);
    SetProtection(BLADE, 1);
    SetProtection(KNIFE, 1);
}

void init(){
    ::init();
}
