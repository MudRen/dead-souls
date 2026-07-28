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
                ({"rune","runes"}) : "这些符文的含义你无法解读。",
                ({"picture","engraving"}) : "一幅近乎滑稽的图案：一只惊恐的兽人被劈成两半。",
                ]) );
    SetRead( ([
                ({"rune","runes"}) : "你看不懂这些符文。"
                ]) );
    AddItem("thing" , "一个东西。");
}
int eventStrike(object target) {
    if( target->GetRace() != "orc" ) return item::eventStrike(target);
    message("environment", "屠兽者之剑发出蓝色的光芒，发出可怕的尖叫声！",
            environment(target));
    return item::eventStrike(target) + random(50)+10;
}
void init(){
    ::init();
}
