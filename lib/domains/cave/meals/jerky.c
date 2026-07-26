#include <lib.h>
#include <meal_types.h>
inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("jerky");
    SetAdjectives(({"unpalatable","dried","flattened","flat",
                "smoked","salted"}));
    SetId(({"meat","strip","strip of jerky","strips of jerky"}));
    SetShort("一条肉干");
    SetLong("一条经过干燥、压平、熏制和腌制的肉条，看起来跟树皮一样硬，更难以下咽。");
    SetNoCondition(1);
    SetMass(15);
    SetStrength(1);
    SetBaseCost("silver", 1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("You gnaw on the jerky and manage to choke it down.",
            "$N gnaws on and chokes down $P strip of jerky.");
}

void init(){
    ::init();
}
