#include <lib.h>

inherit LIB_MATCH;


protected void create() {
    match::create();
    SetKeyName("match");
    SetId("match");
    SetAdjectives( ({ "wooden" }) );
    SetShort("一根火柴");
    SetLong("一根木制火柴，划一下也许能点燃。");
    SetRadiantLight(2);
    SetStrikeChance(50);
    SetMinHeat(10);
    SetFuelRequired(1);
    SetMaxFuel(10);
    SetFuelAmount(10);
    SetRefuelable(0);
    SetMass(5);
    SetBaseCost("silver",2);
    SetBurntValue(1);
}
void init(){
    ::init();
}
