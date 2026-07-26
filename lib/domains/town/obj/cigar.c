#include <lib.h>

inherit LIB_CIGAR;

protected void create() {
    ::create();
    SetKeyName("cigar");
    SetId( ({ "cigar", "cylinder" }) );
    SetAdjectives( ({ "bitterleaf" }) );
    SetShort("一支雪茄");
    SetLong("一根紧密卷起的苦叶制成的圆柱体，设计用于点燃后吸食。");
    SetRadiantLight(2);
    SetFuelRequired(1);
    SetMaxFuel(300);
    SetFuelAmount(30);
    SetRefuelable(0);
    SetMass(5);
    SetBaseCost("silver",30);
    SetBurntValue(0);
    SetClass(10);
}
void init(){
    ::init();
}
mixed eventBurnOut(){
    eventDarken();
    set_heart_beat(0);
    eventDestruct();
    return 1;
}
