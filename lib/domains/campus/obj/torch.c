/*    /domains/Praxis/etc/torch.c
 *    from Dead Souls
 *    created by Descartes of Borg 951023
 */

#include <lib.h>

inherit LIB_TORCH;


protected void create() {
    torch::create();
    SetKeyName("torch");
    SetId( ({ "torch", "old torch", "wooden torch" }) );
    SetAdjectives( ({ "old", "wooden" }) );
    SetShort("旧木火把");
    SetLong("一根旧木火把，一端缠着一些布，浸入了易燃物质中。");
    SetRadiantLight(7);
    SetFuelRequired(1);
    SetMaxFuel(1000);
    SetFuelAmount(1000);
    SetRefuelable(1);
    SetMass(50);
    SetDollarCost(60);
    SetBurntValue(10);
    SetClass(10);
}
void init(){
    ::init();
}
