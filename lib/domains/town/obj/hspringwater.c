#include <lib.h>
#include <meal_types.h>

inherit LIB_BASE_DUMMY;
inherit LIB_FLASK; 

protected void create() {
    base_dummy::create();
    flask::create();
    SetKeyName("water");
    SetId(({"spring","springwater" }));
    SetAdjectives("natural","glowing");
    SetLong("天然泉水的发光水面。");
    SetShort("天然泉水");
    SetFlaskContents("water");
    SetFlaskUses(2);
    SetStrength(5);
    SetMaxFlask(2);
    SetEverFill(1);
    SetMealType(MEAL_DRINK);
    SetNoCondition(1);
    SetInvis(1);
}

mixed CanGet(object ob) { return "#The water stays in place.";}
