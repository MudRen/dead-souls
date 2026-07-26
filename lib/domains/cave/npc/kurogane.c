#include <lib.h>

inherit LIB_SENTIENT;
int throwing;

int CheckOrc(mixed val){
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(val->GetRace() == "orc" || val->GetRace() == "rodent") return 0;
    eventForce("growl at "+val->GetKeyName());
    eventForce("say murdering, genocidal humanoids! Leave us alone!");
    return 1;
}

protected void create() {
    ::create();
    SetKeyName("orc");
    SetId(({"orc","commander","kurogane"}));
    SetAdjectives(({"armored","professional","orc","commander"}));
    SetShort("一个兽人指挥官");
    SetLong("这是一个非常高大的成年兽人，举止专业，目标明确。");
    SetInventory(([
                "/domains/cave/weap/battleaxe" : "wield axe",
                "/domains/cave/armor/chainmail" : "wear chainmail",
                "/domains/cave/armor/orc_tallboot_l" : "wear left boot",
                "/domains/cave/armor/orc_tallboot_r" : "wear right boot",
                ]));
    SetRace("orc");
    SetLevel(10);
    SetClass("fighter");
    SetGender("male");
    SetEncounter(  (: CheckOrc :) );
    SetGuard("south","The commander bars your way!");
}

void init(){
    object env = environment();
    ::init();
    if(env && base_name(env) == "/domains/cave/room/cave"){
        eventForce("go east");
    }
}

void heart_beat(){
    object env = environment();
    ::heart_beat();
    if(env && base_name(env) == "/domains/cave/room/cave"){
        eventForce("go east");
    }
}

int eventDie(mixed agent){
    object player;
    string *quests;
    if(!objectp(player = agent) || !interactive(player)){
        return ::eventDie(agent);
    }
    if(!player->GetQuest("Orc Commander Assassination")){
        player->AddQuest("Cave Explorer II","Orc Commander Assassination");
        write("%^BOLD%^%^RED%^\n\nCONGRATULATIONS!\n%^RESET%^");
        write("%^BOLD%^%^RED%^You have defeated the evil and cruel "+
                "Orc Commander! You have "+
                "earned 12 quest points, and 9500 experience "+
                "points. Nice job!\n\n%^RESET%^");
        player->AddQuestPoints(12);
        player->AddExperiencePoints(9500);
    }
    return ::eventDie(agent);
}

