#include <lib.h>

inherit LIB_SENTIENT;

int CheckOrc(mixed val){
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(val->GetRace() == "orc" || val->GetRace() == "rodent") return 0;
    else eventForce("growl at "+val->GetKeyName());
    return 1;
}

protected void create() {
    ::create();
    SetKeyName("orc");
    SetId(({"orc","chieftain","chiklis"}));
    SetAdjectives(({"orc","armored","professional","chieftain"}));
    SetShort("一个兽人酋长");
    SetLong("这是一个高大的兽人，身上布满了象征权力和威望的华丽纹身和标记。他强壮的体格显然习惯于用武力确立权威。");
    SetInventory(([
                "/domains/cave/weap/longsword" : "wield sword",
                "/domains/cave/armor/platemail" : "wear platemail",
                "/domains/cave/armor/orc_helmet" : "wear helmet",
                "/domains/cave/armor/chainmail_collar" : "wear collar",
                "/domains/cave/armor/armored_boot_l" : "wear left boot",
                "/domains/cave/armor/armored_boot_r" : "wear right boot",
                "/domains/cave/armor/armored_glove_r" : "wear right glove",
                "/domains/cave/armor/armored_glove_l" : "wear left glove",
                ]));
    SetRace("orc");
    SetLevel(10);
    SetClass("fighter");
    SetGender("male");
    SetEncounter(  (: CheckOrc :) );
    SetStat("strength",85);
    SetGuard("/domains/cave/obj/chest2","The orc blocks your theft.");
}

void init(){
    ::init();
}

int eventDie(){
    if(sizeof(GetWieldingLimbs())){
        eventForce("laugh");
        eventForce("speak enjoy your victory, punk!");
        eventForce("pull lever");
    }
    else {
        eventForce("spit");
        eventForce("speak you have no idea what you've done, fool!");
    }
    return ::eventDie();
}
