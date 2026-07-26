#include <lib.h>

inherit LIB_NPC;

int CheckOrc(mixed val){
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(val->GetRace() == "orc") return 0;
    else eventForce("growl at "+val->GetKeyName());
    if(playerp(val) && val->GetRace() != "orc") return 1;
    else return 0;
}

protected void create() {
    npc::create();
    SetKeyName("orc");
    SetId(({"orc"}));
    SetAdjectives(({"armored","professional"}));
    SetShort("一个披甲兽人");
    SetLong("这是一个成年大型兽人。他似乎有着职业军人的气质和使命感，不像你听说过的那些衣衫褴褛、混乱不堪的兽人。他看起来像是在执行任务。");
    SetInventory(([
                "/domains/town/weap/sword" : "wield sword",
                "/domains/town/obj/orc_rucksack" : "wear my sack",
                "/domains/town/armor/leather_armor" : "wear leather armor",
                "/domains/town/armor/orc_boot_l" : "wear left boot",
                "/domains/town/armor/orc_boot_r" : "wear right boot",
                ]));
    SetLevel(1);
    SetRace("orc");
    SetClass("explorer");
    SetGender("male");
    SetEncounter(  (: CheckOrc :) );
}

void init(){
    ::init();
}
