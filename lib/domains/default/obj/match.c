#include <lib.h>

inherit LIB_MATCH;

protected void create() {
    match::create();
    SetKeyName("match");
    SetId("match");
    SetAdjectives( ({ "wooden" }) );
    SetShort("一根木火柴");
    SetLong("一根木火柴， strike it 可能会点燃。");
    SetRadiantLight(2);
    SetStrikeChance(50);
    SetMinHeat(10);
    SetFuelRequired(1);
    SetMaxFuel(10);
    SetFuelAmount(10);
    SetRefuelable(0);
    SetMass(5);
    SetBurntValue(1);
}
