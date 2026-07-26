#include <lib.h>

inherit LIB_TORCH;


protected void create() {
    torch::create();
    SetKeyName("torch");
    SetId( ({ "torch", "old torch", "wooden torch" }) );
    SetAdjectives( ({ "old", "wooden" }) );
    SetShort("一个旧木火把");
    SetLong("一个旧木火把，一端 wrapped around a bit of cloth and dipped into a flamable substance。");
    SetRadiantLight(7);
    SetFuelRequired(1);
    SetMaxFuel(1000);
    SetFuelAmount(1000);
    SetRefuelable(1);
    SetMass(50);
    SetBurntValue(10);
    SetClass(10);
}
void init(){
    ::init();
}
