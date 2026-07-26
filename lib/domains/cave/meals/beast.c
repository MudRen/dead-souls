#include <lib.h>
#include <meal_types.h>
inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("roast beast");
    SetId( ({ "meat","beast","roast","hunk"}) );
    SetAdjectives( ({ "savory","hunk of","spiced","delicious"}) );
    SetShort("一块烤兽肉");
    SetLong("香气四溢、调味十足，这块肉看起来美味可口。");
    SetNoCondition(1);
    SetMass(50);
    SetStrength(15);
    SetBaseCost("silver", 20);
    SetMealType(MEAL_FOOD);
    SetMealMessages("You eat your meat.",
            "$N eats $P hunk of roast beast.");
}

void init(){
    ::init();
}
