#include <lib.h>
#include ROOMS_H
#include <meal_types.h>

inherit LIB_MEAL;

int MealCure(object who);

protected void create() {
    meal::create();
    SetKeyName("pill");
    SetId(({"claritin","loratidine","dose","drug"}));
    SetShort("一片开瑞坦药片");
    SetAdjectives(({"10mg", "10 milligram", "non drowsy","non prescription", "prescription strength"}));
    SetLong("一粒10毫克的感冒片。");
    SetMass(10);
    SetStrength(1);
    SetBaseCost("silver",10);
    SetMealType(MEAL_FOOD);
    SetMealAction((: MealCure :));
    SetMealMessages("你吞下药丸。",
            "$N 吞下一颗药丸。");
}
void init(){
    ::init();
}
int MealCure(object who){
    mixed *stuff;
    int effect = 0;

    if(!who) return 0;

    stuff = all_inventory(who);

    foreach(object ob in stuff){
        if(ob && ob->isGerm() && ob->GetGermName() == "cold virus"){ 
            effect = 1;
            ob->eventMove(ROOM_FURNACE);
        }
    }
    if(effect){
        tell_player(who,"你感觉好了一点。");
    }

    return 1;
} 
