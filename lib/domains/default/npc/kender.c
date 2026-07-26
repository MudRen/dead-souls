#include <lib.h>

inherit LIB_SENTIENT;

int StealAttempt(){
    object *players = get_livings(environment(this_object()),1);
    object *stuff;
    object target;
    string name, thing;
    int which, whether;

    if(sizeof(players)){
        which = random(sizeof(players));
        target = players[which];
        name = target->GetKeyName();
        stuff = all_inventory(target);
        if(!sizeof(stuff) || random(100) > 50) whether = 1;
        if(whether) this_object()->eventForce("steal money from "+name);
        else {
            thing = stuff[random(sizeof(stuff))]->GetKeyName();
            this_object()->eventForce("steal "+thing+" from "+name);
        }
    }
    whether = 0;
    return 1;
}

protected void create() {
    sentient::create();
    SetKeyName("kender");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个肯德人");
    SetLong("身材纤细且相当迷人，肯德人是与霍比特人相关的另一个种族，具有所有的爱玩天性和对他人隐私的额外漠视。肯德人以他们在偷窃他人财物方面的非凡技巧而臭名昭著，据说他们在学会阅读之前就被教导偷窃。其他人对此表示异议，认为肯德人根本不识字。");
    SetClass("thief");
    SetLevel(5);
    SetMelee(1);
    SetRace("kender");
    SetGender("female");
    SetAction(25, ({
                (: StealAttempt :), "!giggle", (: StealAttempt :), "!laugh",
                (: StealAttempt :), "!smile", (: StealAttempt :), "!smirk",
                }) );
}
void init(){
    ::init();
}
