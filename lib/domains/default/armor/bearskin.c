#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("bearskin");
    SetId(({"bearskin","bear skin"}));
    SetAdjectives(({"thick","shaggy"}));
    SetShort("一张厚实蓬松的熊皮");
    SetLong("这是一张厚实的熊皮，可以当作护甲穿戴。"+
            "不幸的是这张皮没有经过鞣制，"+
            "所以气味相当难闻。");
    SetItems( ([
                "hide" : "它没有经过鞣制，会自然腐烂。"
                ]) );
    SetSmell( ([ "default" : "它散发着死亡的气息。" ]) );
    SetMass(75);
    SetDamagePoints(100);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,10);
    SetProtection(KNIFE,10);
    SetArmorType(A_CLOAK);
}
string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " 散发着死亡和腐烂的气息。";
}
