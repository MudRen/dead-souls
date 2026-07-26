#include <lib.h>

inherit LIB_NPC;
object gdude;

int nasty(object dude){
    gdude = dude;
    eventForce("look at "+gdude->GetKeyName());
    eventForce("drool");
    return 1;
}
int CheckHuman(mixed val){
    if(!val) return 0;
    if(!objectp(val)) return 0;
    gdude = val;
    if(val->GetRace() != "human") return 0;
    else { 
        call_out( (: nasty, gdude :) , 2);
    }
    return 1;
}
protected void create() {
    npc::create();
    SetKeyName("troll");
    SetId(({"troll"}));
    SetAdjectives(({"dirty"}));
    SetShort("一个长相凶恶的巨魔");
    SetLong("这是传说中可怕的生物：一个黏糊糊的、绿色的、看起来腐烂的恶魔，有着长长的、 razor-sharp 的爪子和獠牙。");
    SetLevel(3);
    SetRace("troll");
    SetClass("fighter");
    SetGender("male");
    SetMelee(1);
    SetSkill("melee attack",50,50,10);
    SetStat("strength",50,1);
    SetStat("agility",50,1);
    SetStat("coordination",50,1);
    SetStat("speed",50,1);
    AddCurrency("silver",221+random(157));
}
void init(){
    ::init();
}
