#include <lib.h>

inherit "/domains/cave/etc/cave_orc";

int throwing;

int CheckOrc(mixed val){
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(val->GetRace() == "orc" || val->GetRace() == "rodent") return 0;
    eventForce("growl at "+val->GetKeyName());
    if(!this_object()->GetLeader() && sizeof(filter(val->GetFollowers(),
                    (: base_name($1) == base_name(this_object()) :))) < 1){
        eventForce("follow "+val->GetKeyName());
        SetWanderSpeed(1);
    }
    return 1;
}

protected void create() {
    ::create();
    SetKeyName("orc");
    SetId(({"orc"}));
    SetAdjectives(({"adult","male"}));
    SetShort("一个男性兽人");
    SetLong("这是一个成年兽人，比普通人更高大强壮。");
    SetInventory(([
                "/domains/cave/armor/leather_armor" : "wear leather armor",
                "/domains/cave/armor/orc_boot_l" : "wear left boot",
                "/domains/cave/armor/orc_boot_r" : "wear right boot",
                ]));
    SetLevel(2);
    SetMelee(1);
    SetRace("orc");
    SetClass("fighter");
    SetGender("male");
    SetEncounter(  (: CheckOrc :) );
    AddCurrency("gold", random(100));
}

void init(){
    object env = environment();
    ::init();
    if(env && base_name(env) == "/domains/cave/room/cave"){
        eventForce("go east");
    }
}

void heart_beat(){
    object env = room_environment(this_object());
    if(env && base_name(env) == "/domains/cave/room/cave"){
        eventForce("go east");
    }
    torch_action();
    ::heart_beat();
}
