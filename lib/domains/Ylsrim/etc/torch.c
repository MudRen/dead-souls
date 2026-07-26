/*    /domains/Praxis/etc/torch.c
 *    from Dead Souls LPMud
 *    created by Descartes of Borg 951023
 */

#include <lib.h>

inherit LIB_TORCH;

protected void create() {
    torch::create();
    SetKeyName("torch");
    SetId( ({ "torch", "old torch", "wooden torch" }) );
    SetAdjectives( ({ "old", "wooden" }) );
    SetShort("一根旧木火把");
    SetLong("一根旧木火把，一端缠着布条，浸过易燃物质。");
    SetRadiantLight(7);
    SetFuelRequired(1);
    SetMaxFuel(1000);
    SetFuelAmount(1000);
    SetRefuelable(1);
    SetMass(50);
    SetValue(60);
    SetBurntValue(10);
    SetClass(10);
}
