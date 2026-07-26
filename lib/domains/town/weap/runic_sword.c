#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

int CheckOrc(){
    string ret = "这些符文的含义对你来说无法解读。";
    if(this_player()->GetRace() == "orc"){
        write("你感到一种不安的感觉。");
    }
    return write(ret);
}

protected void create() {
    item::create();
    SetKeyName("sword");
    SetId( ({ "short sword", "shortsword"}));
    SetAdjectives( ({ "crafted","finely crafted","short","sharp","fine","runic"}));
    SetShort("一把精制短剑");
    SetLong("这是一把非常好的刀刃，覆盖着古老的符文。");
    SetMass(300);
    SetBaseCost("silver",500);
    SetVendorType(VT_WEAPON);
    SetClass(35);
    SetDamageType(BLADE);
    SetWeaponType("blade");
    SetItems( ([
                ({"rune","runes"}) : (: CheckOrc :),
                ]) );
    SetRead( ([
                ({"rune","runes"}) : "你看不懂这些符文。"
                ]) );
}

void init(){
    ::init();
}
