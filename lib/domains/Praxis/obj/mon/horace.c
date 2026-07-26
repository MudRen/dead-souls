#include <vendor_types.h>
inherit "/lib/std/vendor";

create() {
    ::create();
    SetKeyName("horace");
    SetId( ({ "horace", "vendor", "shop keeper", "keeper", "shopkeeper", "nerd" }) );
    SetShort("霍勒斯，冒险者杂货店的店主");
    SetAggressive( 0);
    SetLevel(12);
    SetLong("他买卖冒险用品。\n"+
            "<help shop> 将为你提供商店命令列表。\n");
    SetNativeLanguage( "eltherian" );
    SetGender("male");
    SetMorality(40);
    SetRace( "elf");
    SetHealthPoints(480);
    AddCurrency("electrum", random(200));
    SetRace("human");
    SetLocalCurrency("electrum");
    SetVendorType(VT_TREASURE);
    SetStorageRoom("/domains/Praxis/storage");
    SetSkill("melee",100);
    SetSkill("bargaining", 150);
    SetProperty("no bump", 1);
}

int is_invincible() {
    SetStaminaPoints(GetMaxStaminaPoints());
    this_object()->eventForce("shout in eltherian 救命啊！！我正在被"+
            previous_object()->query_cap_name()+"攻击");
    return 0;
}
