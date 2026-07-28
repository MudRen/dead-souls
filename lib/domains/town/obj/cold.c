#include <lib.h>
#include ROOMS_H
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
    tell_room(environment(victim), victimname+"看起来脸色苍白，很不舒服。",({victim}) );
    tell_object(victim, "你感到喉咙一阵发痒。");
    return 1;
}

void create(){
    germ::create();
    SetKeyName("tc2");
    SetGermName("cold virus");
    SetId(({"tc2"}));
    SetLong("测试感冒病毒2.1版");
    SetCure(20);
    SetVendorType(VT_TREASURE);
    SetCommunicable(15);
    SetLifeSpan(1200);
    SetType("viral");
    SetInfect((: InfectMess :));
}

void bonuses(){
    if(victim && environment(this_object()) == victim){
        victim->AddStatBonus("intelligence", -5);
        victim->AddStatBonus("strength", -15);
        victim->AddStatBonus("charisma", -35);
        victim->AddStatBonus("durability", -15);
        victim->AddStatBonus("agility", -15);
        victim->AddStatBonus("coordination", -5);
        victim->AddStatBonus("speed", -5);
        victim->AddStatBonus("wisdom", -1);
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

int eventDestruct(){
    this_object()->eventMove(ROOM_FURNACE);
    return ::eventDestruct();
}

int eventMove(mixed dest){
    int ret = germ::eventMove(dest);
    if(environment() && !living(environment())) victim = 0;
    bonuses();
    return ret;
}

int eventSuffer(){
    int x;
    x=random(70);
    if(x < 8) environment()->eventForce("sneeze");
    else if(x < 5) damage1();
    else if(x < 10) damage2();
    else if(x < 15) damage3();
    else if(x < 20) damage4();
    else if(x < 2) damage5();
    return 1; 
}

int DangerLevel(){
    if(victim && victim->GetHealthPoints() < 100) return 100;
    return 1;
}

int FatigueLevel() {
    if(victim && victim->GetStaminaPoints() < 11) return 10;
    return 11;
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + "流着鼻涕。\n"+ob->GetName()+"看起来生病且眩晕。";
}

int damage1(){
    if(victim){
        tell_object(victim,"你感觉很难受。");
        tell_room(environment(victim),victimname+"看起来很痛苦。", ({victim}) );
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-5)-5);
    }
    return 1;
}

int damage2(){
    if(victim){
        tell_object(victim,"你被一阵湿重的咳嗽折磨着。");
        tell_room(environment(victim),victimname+"被一阵湿重的咳嗽折磨着。", ({victim}) );
        if(DangerLevel() != 100) victim->AddHP(-(random(10)+10));
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-10)-5);
    }
    return 1;
}

int damage3(){
    if(victim){
        tell_room(environment(victim),victimname+"发出一声可怜的呻吟。", ({victim}) );
        tell_object(victim,"一阵虚弱袭来，你不由得发出一声痛苦的呻吟。");
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-10)-10);
    }
    return 1;
}

int damage4(){
    if(victim){
        tell_room(environment(victim),victimname+"猛烈地打了个喷嚏，然后低声呜咽。", ({victim}) );
        tell_object(victim,"你猛烈地打了个喷嚏，感觉脑袋快要炸裂了。");
        if(DangerLevel() != 100) victim->AddHP(-(random(10)+2));
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-15)-10);
    }
    return 1;
}

int damage5(){
    if(victim){
        tell_room(environment(victim),victimname+"发出可怕的咕噜咳嗽声，咳出一大团痰。", ({victim}) );
        tell_object(victim,"你咳出一大团痰，不小心又吸了回去，呛得直咳。");
        if(DangerLevel() != 100) victim->AddHP(-(random(20)+10));
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-15)-15);
    }
    return 1;
}


mixed CanGet(object ob) { return "你的手指在鼻涕上打滑。";}
mixed CanDrop(object ob) { return "你的手指在鼻涕上打滑。";}
