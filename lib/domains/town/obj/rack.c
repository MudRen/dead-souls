#include <lib.h>

inherit LIB_SURFACE;
object to;


void create() {
    ::create();
    SetKeyName("rack");
    SetId(({"rack"}));
    SetAdjectives(({"knife","metal","fancy","steel","stainless","stainless-steel"}));
    SetShort("一个刀架");
    SetLong("这是一个精美的不锈钢刀架，上面挂着各种刀具。");
    SetMass(274);
    SetBaseCost("silver",50);
    SetMaxCarry(5);
    SetInventory(([
                //"/domains/town/weap/paring_knife" : 1,
                "/domains/town/weap/butcher_knife" : 1,
                "/domains/town/weap/carving_knife" : 1,
                ]));
    SetCanClose(0);
}
mixed CanGet(object ob) { return "架子纹丝不动。";}
int CanReceive(object ob) {
    if(!ob->GetFancy()) {
        write("这个架子只能放精美的、昂贵的厨刀。");
        return 0;
    }
    else return 1;
}
void init(){
    ::init();
}
