#include <lib.h>
#include <vendor_types.h>
#include <damage_types.h>
inherit LIB_GERM;
int damage1();
int damage2();
int damage3();
int damage4();
int damage5();
int DangerLevel();
object victim,where;
string victimname;

int InfectMess(object ob){
    victim=ob;
    victimname=victim->GetName();
    tell_room(environment(victim), victimname+"看起来又惊又恶心。",({victim}) );
    tell_object(victim, "你惊讶又恶心地发现虱子在你身上爬来爬去。");
    return 1;
}

void create(){
    germ::create();
    SetKeyName("tf1");
    SetId(({"tf2"}));
    SetLong("虱子病毒1版");
    SetCure(20);
    SetVendorType(VT_TREASURE);
    SetCommunicable(50);
    SetLifeSpan(777);
    SetType("parasite");
    SetInfect((: InfectMess :));
}

void bonuses(){
    if(victim && environment(this_object()) == victim){
        victim->AddStatBonus("intelligence", -15);
        victim->AddStatBonus("strength", -25);
        victim->AddStatBonus("charisma", -45);
        victim->AddStatBonus("durability", -25);
        victim->AddStatBonus("agility", -25);
        victim->AddStatBonus("coordination", -15);
        victim->AddStatBonus("speed", -15);
        victim->AddStatBonus("wisdom", -2);
    }
    else if(victim) {
        foreach( string stat in ({"intelligence", "strength",
                    "charisma", "durability", "agility", "coordination", "speed", "wisdom"})){
            victim->RemoveStatBonus(stat);
        }
    }
    return;
}


void init(){
    germ::init();
    bonuses();
}

int eventSuffer(){
    int x;
    x=random(500);
    if(x < 5) damage1();
    else if(x < 10) damage2();
    else if(x < 15) damage3();
    else if(x < 20) damage4();
    return 1;
}

int DangerLevel(){
    if(victim->GetHealthPoints() < 20) return 100;
    return 1;
}

int FatigueLevel() {
    if(victim->GetStaminaPoints() < 11) return 10;
    return 11;
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + "看起来不舒服，蓬头垢面。";
}

int damage1(){
    tell_object(victim,"你浑身痒得要命。");
    tell_room(environment(victim),victimname+"看起来很不自在。", ({victim}) );
    return 1;
}

int damage2(){
    tell_object(victim,"你不由自主地开始抓挠那令人发疯的痒。");
    tell_room(environment(victim),victimname+"拼命地抓着自己。", ({victim}) );
    return 1;
}

int damage3(){
    tell_room(environment(victim),victimname+"疯狂地抓挠自己，抓破了皮，出了血。", ({victim}) );
    tell_object(victim,"你疯狂地抓挠自己，抓破了皮，出了血。");
    if(DangerLevel() != 100) victim->eventReceiveDamage(this_object(),DISEASE,random(5)+4,0,"torso");
    return 1;
}

int damage4(){
    tell_room(environment(victim),victimname+"看起来恶心极了。", ({victim}) );
    tell_object(victim,"你感到恶心，因为你能感觉到虱子在身上爬。");
    return 1;
}

mixed CanGet(object ob) { return "你根本无法摆脱这些寄生虫。";}
mixed CanDrop(object ob) { return "你根本无法摆脱这些寄生虫。";}
