#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;
inherit LIB_READ;

protected void create() {
    item::create();
    SetKeyName("Orc Slayer");
    SetId( ({ "orcslayer", "orc slayer","sword", "short sword", "shortsword"}));
    SetAdjectives( ({ "crafted","finely crafted","short","sharp","fine"}));
    SetShort("一把精美打造的短剑");
    SetLong("这是一把非常精美的 blade， covered with ancient runes。 Engraved on it is a picture of the sword slicing an orc。");
    SetMass(300);
    SetVendorType(VT_WEAPON);
    SetClass(150);
    SetDamageType(BLADE);
    SetWeaponType("blade");
    SetItems( ([
                ({"rune","runes"}) : "这些 runes' meaning is undecipherable to you。",
                ({"picture","engraving"}) : "一个 almost comical image of a startled orc sliced in half。",
                ]) );
    SetRead( ([
                ({"rune","runes"}) : "你不理解它们。"
                ]) );
}

int eventStrike(object target) {
    if( target->GetRace() != "orc" ) return item::eventStrike(target);
    message("environment", "兽人杀手剑发出蓝色光芒并发出可怕的尖叫声！",
            environment(target));
    return item::eventStrike(target) + random(50)+10;
}
