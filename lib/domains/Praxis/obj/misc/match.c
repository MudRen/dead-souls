#include <lib.h>

inherit LIB_MATCH;

protected void create() {
    match::create();
    SetKeyName("match");
    SetId("match");
    SetAdjectives( ({ "wooden" }) );
    SetShort("一根火柴");
    SetLong("一根如果你划它可能会点燃的火柴。");
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
