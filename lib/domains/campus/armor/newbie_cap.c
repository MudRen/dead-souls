#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
//inherit "/lib/events/read";

string eventReadBill(){
    return "帽子正面写着：\"吻我，我是新手！\"";
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
                ({"brim","bill","front"}) : "不知为何，这顶帽子的正面镀有一层精致的秘银……"+
                "这是人类已知的最坚固、最昂贵的物质之一。",
                ({"writing","letters"}): "帽子正面写着一些字。也许你可以\"阅读帽子上的字\"",
                ]) );

    SetRead( ([
                ({"front","writing","letters"}) : "帽子正面写着：\"吻我，我是新手！\"",
                ]) );
    SetDefaultRead("default", "帽子正面写着：\"吻我，我是新手！\"");
}
