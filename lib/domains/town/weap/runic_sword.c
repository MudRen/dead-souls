#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

int CheckOrc(){
    string ret = "The runes' meaning is undecipherable to you.";
    if(this_player()->GetRace() == "orc"){
        write("You get an uneasy feeling.");
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
                ({"rune","runes"}) : "You do not understand them."
                ]) );
}

void init(){
    ::init();
}
