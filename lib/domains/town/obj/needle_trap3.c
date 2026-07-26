// For examples of valid trap types, see /include/boobytraps.h
//
// Boobytraps are two objects. The "pre" trap object, which is the tangible
// object you can hold. Then there is the "post" object, an invisible
// shadow that attaches itself to the target. This is the "pre" object. Once
// the trap is set, this object is removed from the game, and the shadow
// object attaches itself to the target, waiting for the appropriate stimulus.
//
// The shadow object is indicated in the SetShadowObject directive.

#include <lib.h>
#include <boobytraps.h>

inherit LIB_BOOBYTRAP_OBJECT;

void create(){
    ::create();
    SetKeyName("trap");
    SetId( ({ "trap" }) );
    SetAdjectives( ({ "simple","weapon", "poison", "needle" }) );
    SetShort("一个武器陷阱");
    SetLong("这是一个简单的毒针陷阱，设计为在拿起武器时触发。");
    SetShadowObject("/shadows/needle_trap");
    SetTrapType(BOOBYTRAP_WIELD);
    SetMass(50);
    SetAutoResets(2);
    SetBaseCost(100);
}

void init(){
    ::init();
}
