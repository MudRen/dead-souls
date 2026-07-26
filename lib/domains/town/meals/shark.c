/*    /domains/Ylsrim/fish/shark.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <meal_types.h>
#include <dirs.h>
#include <damage_types.h>

inherit LIB_FISH;

void BiteMe(object who);
protected void create() {
    fish::create();
    SetKeyName("bull shark");
    SetId( ({ "shark", "bull shark" }) );
    SetShort("一条牛鲨");
    SetLong("这是一条巨大的长鱼，有锋利的牙齿和肉食性的本能。它看起来很危险。");
    SetMealType(MEAL_FOOD);
    SetMass(100); 
    SetStrength(50);
    SetBaseCost("silver", 10);
    SetFight(40);
    SetFood("/domains/town/meals/shark");
}
int eventCatch(object who, object pole) { 
    call_out((: BiteMe, who :), 0);
    return 1;
}
void BiteMe(object who) {
    who->eventPrint("鲨鱼在死前咬了你一口！");
    environment(who)->eventPrint("鲨鱼在死前咬了" + who->GetName() +
            "一口！", who);
    who->eventReceiveDamage(this_object(), BITE, random(30), 0,
            who->GetRandomLimb("right hand"));
}
void init(){
    ::init();
}
