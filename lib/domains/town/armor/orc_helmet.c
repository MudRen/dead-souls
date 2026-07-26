#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

varargs int CheckOrc(object who, mixed where);

protected void create(){
    armor::create();
    SetKeyName("orc helmet");
    SetId(({"helmet","skull"}));
    SetAdjectives(({"bear","bone","skull","orc"}));
    SetShort("一顶熊骨头盔");
    SetLong("这是一顶由熊的硬骨制成的头盔，看起来非常原始和野蛮。");
    SetMass(150);
    SetBaseCost("silver",100);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
    SetWear( (: CheckOrc :) );
}

varargs int CheckOrc(object who, mixed where){
    string race = who->GetRace();
    object env = environment(who);
    if( race == "orc"  || race == "half-orc"){
        who->eventPrint("当你戴上这熊骨头盔时，你几乎能感受到熊的力量。");
        if(env) tell_room(env, who->GetName()+" wears "+
                GetShort()+".", ({who}));
        return 1;
    }
    else {
        who->eventPrint("这头盔似乎是为兽人的体型设计的，不适合你。");
        return 0;
    }
}

void init(){
    ::init();
}
