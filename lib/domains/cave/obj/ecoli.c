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
object victim,where;
string victimname;

int CalculateDuration(){
    int ret = 600;
    ret += random(9000);
    return ret;
}

int InfectMess(object ob){
    victim=ob;
    victimname=victim->GetName();
    tell_room(environment(victim), victimname+"看起来虚弱而眩晕。",({victim}) );
    tell_object(victim, "你感到虚弱和头晕。");
    return 1;
}

void create(){
    germ::create();
    SetKeyName("e coli");
    SetGermName("e. coli");
    SetId(({"ecoli"}));
    SetLong("大肠杆菌");
    SetCure(40);
    SetCommunicable(0);
    SetLifeSpan( (: CalculateDuration :) );
    SetType("viral");
    SetInfect((: InfectMess :));
}

void bonuses(){
    if(victim && environment(this_object()) == victim){
        victim->AddStatBonus("intelligence", 
                -(percent_of(20,this_player()->GetBaseStatLevel("intelligence"))));
        victim->AddStatBonus("strength", 
                -(percent_of(75,this_player()->GetBaseStatLevel("strength"))));
        victim->AddStatBonus("charisma", 
                -(percent_of(65,this_player()->GetBaseStatLevel("charisma"))));
        victim->AddStatBonus("durability", 
                -(percent_of(65,this_player()->GetBaseStatLevel("durability"))));
        victim->AddStatBonus("agility", 
                -(percent_of(40,this_player()->GetBaseStatLevel("agility"))));
        victim->AddStatBonus("coordination", 
                -(percent_of(45,this_player()->GetBaseStatLevel("coordination"))));
        victim->AddStatBonus("speed", 
                -(percent_of(55,this_player()->GetBaseStatLevel("speed"))));
        victim->AddStatBonus("wisdom", 
                -(percent_of(10,this_player()->GetBaseStatLevel("wisdom"))));
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
    x=random(1000);
    if(x < 5) damage1();
    else if(x < 10) damage2();
    else if(x < 15) damage3();
    else if(x < 20) damage4();
    else if(x < 30) damage5();
    return 1;
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + "看起来凌乱不堪。\n"+ob->GetName()+"看起来病得很重，神志不清。";
}

int damage1(){
    if(victim){
        tell_object(victim,"你感到虚弱和不适。");
        tell_room(environment(victim),victimname+"看起来苍白而病态。", ({victim}) );
        victim->AddStaminaPoints(random(-2)-2);
    }
    return 1;
}

int damage2(){
    if(victim){
        tell_object(victim,"你被一阵可怕的干呕所折磨。");
        tell_room(environment(victim),victimname+"被一阵可怕的干呕所折磨。", ({victim}) );
        victim->AddHP(-(random(3)+3));
        victim->AddStaminaPoints(-(random(3))-3);
    }
    return 1;
}

int damage3(){
    if(victim){
        tell_room(environment(victim),victimname+"发出一声不适的呻吟。", ({victim}) );
        tell_object(victim,"当一阵虚弱袭来时，你发出一声不适的呻吟。");
        victim->AddStaminaPoints(-(random(4))-4);
    }
    return 1;
}

int damage4(){
    if(victim){
        tell_room(environment(victim),victimname+"剧烈地干呕，然后吐出一大口呕吐物在地上。", ({victim}) );
        tell_object(victim,"你剧烈地干呕，然后吐出一大口呕吐物在地上。");
        victim->AddHP(-(random(5)+5));
        victim->AddStaminaPoints(-(random(5))-5);
    }
    return 1;
}

int damage5(){
    if(victim){
        if(victim->GetPosition() != 1){
            tell_room(environment(victim),victimname+"发出一阵可怕的放屁声，无助地倒在地板上，弄脏了"+objective(victim)+"自己。", ({victim}) );
            tell_object(victim,"你发出一阵可怕的放屁声，无助地倒在地板上，弄脏了自己。");
            victim->SetPosition(1);
        }
        if(victim->GetPosition() == 1){
            tell_room(environment(victim),victimname+"发出一阵可怕的放屁声，"+nominative(victim)+"无助地躺在地上。", ({ victim}));
            tell_object(victim,"你发出一阵可怕的放屁声，无助地躺在地上。");
        }
        victim->AddHP(-(random(10)+10));
        victim->AddStaminaPoints(-(random(10))-10);
    }
    return 1;
}

mixed CanGet(object ob) { return "你不能那样做。";}
mixed CanDrop(object ob) { return "你不能那样做。";}
