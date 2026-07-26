#include <lib.h>

inherit "/domains/cave/etc/cave_orc";

int throwing;

int CheckOrc(mixed val){
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(val->GetRace() == "orc" || val->GetRace() == "rodent") return 0;
    return 1;
}

protected void create() {
    ::create();
    SetKeyName("orc");
    SetId(({"orc","female"}));
    SetAdjectives(({"adult","female"}));
    SetShort("一个女性兽人");
    SetLong("这是一个成年兽人，比普通人更高大强壮。");
    SetInventory(([
                "/domains/cave/armor/orc_dress" : "wear dress",
                ]));
    SetLevel(2);
    SetMelee(1);
    SetRace("orc");
    SetClass("fighter");
    SetGender("female");
    SetEncounter(  (: CheckOrc :) );
    AddCurrency("gold", random(100));
}

void init(){
    ::init();
}

void heart_beat(){
    torch_action();
    ::heart_beat();
}
