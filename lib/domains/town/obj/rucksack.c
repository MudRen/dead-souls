#include <lib.h>

#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create() {
    ::create();
    SetKeyName("rucksack");
    SetId(({"ruck","sack"}));
    SetAdjectives(({"sturdy","green","olive","olive-green","od green","od-green"}));
    SetShort("一个结实的橄榄绿帆布背包");
    SetLong("这是一个大而结实的帆布背包，由某种粗糙的绿色织物制成。");
    SetMass(100);
    SetDollarCost(200);
    SetCanClose(1);
    SetClosed(1);
    SetMaxCarry(1000);
    SetDamagePoints(100);
    SetArmorType(A_VEST);
    SetInventory(([
                "/domains/town/obj/torch" : 1,
                "/domains/town/obj/match" : 3,
                ]));
}
void init(){
    ::init();
}
