#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("goggles");
    SetId(({"goggles"}));
    SetAdjectives(({"thick","driving","protective","eyewear"}));
    SetShort("驾驶护目镜");
    SetLong("一副防护护目镜，适合在危险环境中佩戴。");
    SetMass(5);
    SetBaseCost("silver",30);
    SetArmorType(A_VISOR);
}

void init(){
    ::init();
}

int eventReceiveDamage(mixed agent, int type, int amt, int i, mixed* l){
    if(GetWorn()){
        tell_object(environment(this_object()), "The goggles! They "+
                "do nothing!");
    }
    return ::eventReceiveDamage(agent, type, amt, i, l);
}


