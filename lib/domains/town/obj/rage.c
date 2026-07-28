#include <lib.h>
#include ROOMS_H
#include <vendor_types.h>
#include <damage_types.h>

#define PLAYER_INFECTABLE 0

inherit LIB_GERM;
int damage1();
int damage2();
int damage3();
int damage4();
int damage5();
int DangerLevel();
object global_ob,victim,where;
string victimname;

int MakeHostile(object ob){
    object *meat = get_livings(environment(ob));
    global_ob = ob;
    meat = filter(meat, (: !(base_name($1) == base_name(global_ob)) :));
    meat = filter(meat, (: !($1->GetInvis()) :));
    foreach(object new_meat in meat){
        ob->AddEnemy(new_meat);
    }
    return 1;
}

int InfectMess(object ob){
    victim=ob;
    victimname=victim->GetName();
    if(interactive(victim) && !PLAYER_INFECTABLE) {
        eventDestruct();
        return 1;
    }
    tell_room(environment(victim), "%^BOLD%^RED%^"+victimname+"突然发出一声令人毛骨悚然的尖叫！%^RESET%^",({victim}) );
    tell_object(victim, "%^BOLD%^RED%^你尖叫着被一阵无法控制的狂怒所占据！%^RESET%^");
    ob->SetEncounter(100);
    ob->SetMelee(1);
    if(ob->GetRace() != "human" && ob->GetRace() != "orc") MakeHostile(ob);
    return 1;
}

void create(){
    germ::create();
    SetKeyName("rage virus");
    SetGermName("rage virus");
    SetId(({"rv2"}));
    SetLong("狂怒病毒2版");
    SetCure(20);
    SetCommunicable(30);
    SetLifeSpan(999);
    SetType("viral");
    SetInfect((: InfectMess :));
}

void bonuses(){
    if(!this_object()) return;
    if(victim && environment(this_object()) == victim){
        victim->AddStatBonus("intelligence", -25);
        victim->AddStatBonus("strength", 35);
        victim->AddStatBonus("charisma", -35);
        victim->AddStatBonus("durability", 35);
        victim->AddStatBonus("agility", 35);
        victim->AddStatBonus("coordination", 35);
        victim->AddStatBonus("speed", 35);
        victim->AddStatBonus("wisdom", -25);
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
    if(!this_object()) return;
    germ::init();
    bonuses();
}

int eventDestruct(){
    this_object()->eventMove(ROOM_FURNACE);
    return ::eventDestruct();
}

int eventMove(mixed dest){
    int ret = germ::eventMove(dest);
    if(this_object() && environment() && !living(environment())) victim = 0;
    bonuses();
    return ret;
}

int eventSuffer(object ob){
    int x;
    if(!ob) return;
    x=random(50);
    if(x < 5) damage1();
    else if(x < 10) damage2();
    else if(x < 15) damage3();
    else if(x < 20) damage4();
    else if(x < 2) damage5();
    return 1; 
}

int DangerLevel(){
    if(victim && victim->GetHealthPoints() < 2) return 100;
    return 1;
}

int FatigueLevel() {
    if(victim && victim->GetStaminaPoints() < 11) return 10;
    return 11;
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return "%^BOLD%^RED%^"+ob->GetName() + "看起来疯狂而暴怒！%^RESET%^";
}

int damage1(){
    if(victim){
        tell_object(victim,"%^BOLD%^RED%^你感到被仇恨和疯狂所蒙蔽！%^RESET%^");
        tell_room(environment(victim),victimname+"看起来疯狂至极，口水不受控制地流下。", ({victim}) );
        victim->AddStaminaPoints(random(50)+10);
        victim->AddStatBonus("strength", 10);
        victim->AddStatBonus("durability", 10);
        victim->AddStatBonus("agility", 10);
        victim->AddStatBonus("coordination", 10);
        victim->AddStatBonus("speed", 10);
        MakeHostile(victim);
    }
    return 1;
}

int damage2(){
    if(victim){
        tell_object(victim,"%^BOLD%^RED%^你感到全身被怒火引爆！%^RESET%^");
        tell_room(environment(victim),victimname+"在暴怒中颤抖。", ({victim}) );
        victim->AddStaminaPoints(random(50)+20);
        victim->AddStatBonus("strength", 20);
        victim->AddStatBonus("durability", 20);
        victim->AddStatBonus("agility", 20);
        victim->AddStatBonus("coordination", 20);
        victim->AddStatBonus("speed", 20);
        MakeHostile(victim);
        victim->AddHP(-(random(50)+10));
    }
    return 1;
}

int damage3(){
    if(victim){
        tell_room(environment(victim),victimname+"发出一声可怕的怒吼！", ({victim}) );
        tell_object(victim,"%^BOLD%^RED%^一阵狂怒的痉挛穿过你的身体，你发出一声可怕的怒吼！%^RESET%^");
        victim->AddStaminaPoints(random(60)+30);
        victim->AddStatBonus("strength", 30);
        victim->AddStatBonus("durability", 30);
        victim->AddStatBonus("agility", 30);
        victim->AddStatBonus("coordination", 30);
        victim->AddStatBonus("speed", 30);
        MakeHostile(victim);
        victim->AddHP(-(random(60)+30));
    }
    return 1;
}

int damage4(){
    if(victim){
        tell_room(environment(victim),victimname+"全身疯狂地颤抖，溅出热血、汗水和唾液。", ({victim}) );
        tell_object(victim,"%^BOLD%^RED%^你的全身不受控制地颤抖，到处喷溅着血、汗和口水。%^RESET%^");
        victim->AddStaminaPoints(random(70)+40);
        victim->AddStatBonus("strength", 40);
        victim->AddStatBonus("durability", 40);
        victim->AddStatBonus("agility", 40);
        victim->AddStatBonus("coordination", 40);
        victim->AddStatBonus("speed", 40);
        MakeHostile(victim);
        victim->AddHP(-(random(70)+40));

        foreach(object bystander in get_livings(environment(victim))){
            if(bystander && random(100) > 50 && this_object()) 
                eventInfect(bystander);
        }
    }
    return 1;
}

int damage5(){
    if(victim){
        tell_room(environment(victim),victimname+"发出可怕的咕噜咳嗽声，咳出一大团痰。", ({victim}) );
        tell_object(victim,"你咳出一大团痰，不小心又吸了回去，呛得直咳。");
        //Fix below courtesy of Jonez
        victim->AddStaminaPoints(random(80)+50);
        victim->AddStatBonus("strength", 50);
        victim->AddStatBonus("durability", 50);
        victim->AddStatBonus("agility", 50);
        victim->AddStatBonus("coordination", 50);
        victim->AddStatBonus("speed", 50);
        MakeHostile(victim);
        victim->AddHP(-(random(80)+50));
    }
    return 1;
}


mixed CanGet(object ob) { return "你的手指在鼻涕上打滑。";}
mixed CanDrop(object ob) { return "你的手指在鼻涕上打滑。";}
