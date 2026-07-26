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
    SetLong("这是一张厚实的熊皮，可以穿戴在身上提供保暖和防护。");
    SetItems( ([
                "hide" : "It is untanned and subject "+
                "to natural decomposition."
                ]) );
    SetSmell( ([ "default" : "It reeks of death." ]) );
    SetMass(75);
    SetBaseCost("silver",10);
    SetProtection(BLADE,5);
    SetProtection(KNIFE,5);
    SetArmorType(A_CLOAK);
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " reeks of death and decay.";
}

void init(){
    ::init();
}
