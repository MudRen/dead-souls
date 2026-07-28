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
    SetMealMessages("你啃着肉干，勉强咽了下去。",
            "$N 啃着$P肉干，勉强咽了下去。");
}

void init(){
    ::init();
}
