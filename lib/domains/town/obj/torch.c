#include <lib.h>

inherit LIB_TORCH;

protected void create() {
    torch::create();
    SetKeyName("torch");
    SetId( ({ "torch", "old torch", "wooden torch" }) );
    SetAdjectives( ({ "old", "wooden" }) );
    SetShort("一支旧木火把");
    SetLong("一支旧木火把，末端缠着一些布。点燃它可以照明。");
    SetRadiantLight(7);
    SetFuelRequired(1);
    SetMaxFuel(1000);
    SetFuelAmount(1000);
    SetRefuelable(1);
    SetMass(20);
    SetBaseCost("silver",60);
    SetBurntValue(10);
    SetClass(10);
}

void init(){
    ::init();
}
