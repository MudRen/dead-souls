/*    /domains/Praxis/etc/torch.c
 *    from Dead Souls LPMud
 *    created by Descartes of Borg 951023
 */

#include <lib.h>

inherit LIB_MATCH;

protected void create() {
    match::create();
    SetKeyName("match");
    SetId("match");
    SetAdjectives( ({ "wooden" }) );
    SetShort("一根木火柴");
    SetLong("一根木火柴，划一下也许能点着。");
    SetRadiantLight(2);
    SetStrikeChance(50);
    SetMinHeat(10);
    SetFuelRequired(1);
    SetMaxFuel(10);
    SetFuelAmount(10);
    SetRefuelable(0);
    SetMass(5);
    SetValue(2);
    SetBurntValue(1);
}
