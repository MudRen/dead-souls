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
    SetLong("身材 slender and rather attractive，肯德人是与 hobbits 相关的另一个种族，具有所有的 playfulness and a little extra disregard for other people's privacy。肯德人以他们 extraordinary skill in relieving others of their property 而 infamous， and it is said they are taught to steal before being taught to read。 Others dispute this, arguing kenders don't read at all。");
    SetClass("thief");
    SetLevel(5);
    SetMelee(1);
    SetRace("kender");
    SetGender("female");
    SetAction(25, ({
                (: StealAttempt :),
                }) );
}
void init(){
    ::init();
}
