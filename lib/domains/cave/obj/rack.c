#include <lib.h>

inherit LIB_SURFACE;
object to;


void create() {
    ::create();
    SetKeyName("rack");
    SetId(({"rack"}));
    SetAdjectives(({"knife","metal","fancy","steel","stainless","stainless-steel"}));
    SetShort("一个杯子架");
    SetLong("这是一个带挂钩的架子，用来挂杯子。");
    SetMass(274);
    SetBaseCost("silver",50);
    SetMaxCarry(100);
    SetInventory(([
                "/domains/cave/obj/mug" : 4,
                "/domains/cave/obj/stein" : 1,
                ]));
    SetCanClose(0);
}
mixed CanGet(object ob) { return "这个架子纹丝不动。";}
int CanReceive(object ob) {
    if(!inherits(LIB_FLASK,ob)){
        write("这是一个只放饮用器具的架子。");
        return 0;
    }
    else return 1;
}
void init(){
    ::init();
}
