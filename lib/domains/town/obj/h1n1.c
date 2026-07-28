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
    tell_room(environment(victim), victimname+"看起来虚弱且头晕目眩。",({victim}) );
    tell_object(victim, "你感到虚弱且头晕。");
    return 1;
}

void create(){
    germ::create();
    SetKeyName("tf3");
    SetGermName("flu virus");
    SetId(({"tf3"}));
    SetLong("测试流感病毒3版");
    SetCure(20);
    SetCommunicable(30);
    SetLifeSpan(900);
    SetType("viral");
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
    x=random(500);
    if(x < 2) environment()->eventForce("sneeze");
    else if(x < 5) damage1();
    else if(x < 10) damage2();
    else if(x < 15) damage3();
    else if(x < 20) damage4();
    else if(x > 98) damage5();
    return 1;
}

int DangerLevel(){
    if(victim && victim->GetHealthPoints() < 50) return 100;
    return 1;
}

int FatigueLevel() {
    if(victim && victim->GetStaminaPoints() < 11) return 10;
    return 11;
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + "蓬头垢面。\n"+ob->GetName()+"看起来病得很重，神志不清。";
}

int damage1(){
    if(victim){
        tell_object(victim,"你感到虚弱不适。");
        tell_room(environment(victim),victimname+"看起来脸色苍白。", ({victim}) );
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-15)-15);
    }
    return 1;
}

int damage2(){
    if(victim){
        tell_object(victim,"你被一阵可怕的干咳折磨着。");
        tell_room(environment(victim),victimname+"被一阵可怕的干咳折磨着。", ({victim}) );
        if(DangerLevel() != 100) victim->AddHP(-(random(20)+10));
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-10)-5);
    }
    return 1;
}

int damage3(){
    if(victim){
        tell_room(environment(victim),victimname+"发出一声痛苦的呻吟。", ({victim}) );
        tell_object(victim,"一阵虚弱袭来，你发出一声痛苦的呻吟。");
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-10)-10);
    }
    return 1;
}

int damage4(){
    if(victim){
        tell_room(environment(victim),victimname+"剧烈地干呕，然后吐出一大滩呕吐物。", ({victim}) );
        tell_object(victim,"你剧烈地干呕，然后吐出一大滩呕吐物。");
        if(DangerLevel() != 100) victim->AddHP(-(random(30)+15));
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-25)-20);
    }
    return 1;
}

int damage5(){
    if(victim){
        if(victim->GetPosition() != 1){
            tell_room(environment(victim),victimname+"发出一声可怕的屁响，无助地倒在地上，弄脏了自己。", ({victim}) );
            tell_object(victim,"你发出一声可怕的屁响，无助地倒在地上，弄脏了自己。");
            victim->SetPosition(1);
        }
        if(victim->GetPosition() == 1){
            tell_room(environment(victim),victimname+"躺在地上无助地发出一声可怕的屁响。", ({ victim}));
            tell_object(victim,"你躺在地上无助地发出一声可怕的屁响。");
        }
        if(DangerLevel() != 100) victim->AddHP(-(random(35)+15));
        if(FatigueLevel() > 10) victim->AddStaminaPoints(random(-35)-25);
    }
    return 1;
}

mixed CanGet(object ob) { return "你的手指在鼻涕上打滑。";}
mixed CanDrop(object ob) { return "你的手指在鼻涕上打滑。";}
