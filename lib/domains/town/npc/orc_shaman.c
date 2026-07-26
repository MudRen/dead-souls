#include <lib.h>

inherit LIB_NPC;

int CheckOrc(mixed val){
    string *allowed_races = ({ "orc", "half-orc", "bear" });
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(member_array(val->GetRace(), allowed_races) != -1) return 0;
    else eventForce("growl at "+val->GetKeyName());
    return 1;
}

protected void create() {
    npc::create();
    SetKeyName("orc shaman");
    SetId(({"orc","shaman"}));
    SetAdjectives(({"dirty"}));
    SetShort("兽人萨满");
    SetLong("这个兽人与你见过的其他兽人不同。他身上散发着超自然的凶猛气息，比其他兽人更大、更坚韧、更凶恶。");
    SetLevel(1);
    SetRace("orc");
    SetClass("fighter");
    SetGender("male");
    SetMaxHealthPoints(200);
    SetEncounter(  (: CheckOrc :) );
    SetInventory(([
                "/domains/town/weap/gstaff":"wield staff",
                "/domains/town/weap/orcslayer":1,
                "/domains/town/armor/orc_helmet": "wear helmet",
                "/domains/town/armor/bearskin": "wear bearskin",
                ]) );

}
void init(){
    ::init();
}
