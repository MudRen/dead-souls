#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;


protected void create() {
    item::create();
    SetKeyName("Orc Slayer");
    SetId( ({ "orcslayer", "orc slayer","sword", "short sword", "shortsword"}));
    SetAdjectives( ({ "crafted","finely crafted","short","sharp","fine"}));
    SetShort("一把精制短剑");
    SetLong("这是一把非常好的刀刃，上面覆盖着古老的符文。刻着一幅剑斩兽人的图案。");
    SetMass(300);
    SetBaseCost("silver",500);
    SetVendorType(VT_WEAPON);
    SetClass(35);
    SetDamageType(BLADE);
    SetWeaponType("blade");
    SetItems( ([
                ({"rune","runes"}) : "The runes' meaning is undecipherable to you.",
                ({"picture","engraving"}) : "An almost comical image of a startled orc sliced in half.",
                ]) );
    SetRead( ([
                ({"rune","runes"}) : "You do not understand them."
                ]) );
    AddItem("thing" , "A thing.");
}
int eventStrike(object target) {
    if( target->GetRace() != "orc" ) return item::eventStrike(target);
    message("environment", "The orc slayer sword glows blue and emits a ghastly shrieking sound!",
            environment(target));
    return item::eventStrike(target) + random(50)+10;
}
void init(){
    ::init();
}
