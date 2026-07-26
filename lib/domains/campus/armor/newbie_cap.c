#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
//inherit "/lib/events/read";

string eventReadBill(){
    return "The front of the cap reads: \"Kiss me, I'm a newbie!\"";
}
protected void create(){
    armor::create();
    SetKeyName("baseball cap");
    SetId(({"cap","hat"}));
    SetAdjectives(({"baseball"}));
    SetShort("棒球帽");
    SetLong("这顶棒球帽看起来很普通，除了帽边是精致的科林斯皮革，帽檐镀了一层看起来是纯秘银的金属。帽子正面写着一些字。");
    SetMass(50);
    SetDollarCost(100);
    SetDamagePoints(20);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
    SetItems( ([
                ({"brim","bill","front"}) : "For some reason the front of this cap "+
                "is plated with a fine layer of mithril...one of the strongest "+
                "and most expensive substances known to man.",
                ({"writing","letters"}): "Something is written on the front of the "+
                "cap. Perhaps you could \"read writing on cap\"",
                ]) );

    SetRead( ([
                ({"front","writing","letters"}) : "The front of the cap reads: \"Kiss me, I'm a newbie!\"",
                ]) );
    SetDefaultRead("default", "The front of the cap reads: \"Kiss me, I'm a newbie!\"");
}
