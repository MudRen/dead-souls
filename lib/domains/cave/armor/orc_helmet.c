#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

varargs int CheckOrc(object who, mixed where);

protected void create(){
    armor::create();
    SetKeyName("orc helmet");
    SetId(({"helmet"}));
    SetAdjectives(({"bear","bone","skull","orc"}));
    SetShort("一顶熊骨头盔");
    SetLong("这是一顶用熊的坚硬骨骼制成的头盔，经过某种厚树脂处理以防碎裂。");
    SetMass(180);
    SetBaseCost("silver",100);
    SetDamagePoints(100);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
    SetWear( (: CheckOrc :) );
}

varargs int CheckOrc(object who, mixed where){
    object env = environment(who);
    if( who->GetRace() == "orc" ) {
        who->eventPrint("当你戴上熊的头骨时，你几乎能感受到熊的力量。");
        if(env) tell_room(env, who->GetName()+" wears "+GetShort()+
                ".", ({who}));
        return 1;
    }
    else {
        who->eventPrint("这顶头盔似乎是为兽人的体型设计的。它不适合你。");
        return 0;
    }
}
