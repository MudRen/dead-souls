#include <lib.h>
#include <damage_types.h>

inherit LIB_SURFACE;
object to;

void create() {
    ::create();
    SetKeyName("rack");
    SetId(({"rack"}));
    SetAdjectives(({"knife","metal","fancy","steel","stainless","stainless-steel"}));
    SetShort("一个武器架");
    SetLong("这是一个刃 weapons rack here for your combat testing convenience。");
    SetNoCondition(1);
    SetMass(274);
    SetBaseCost("silver",50);
    SetMaxCarry(5000);
    SetInventory(([
                "/domains/default/weap/sharpsword" : ({ 1800, 5 }),
                ]));
    SetCanClose(0);
    SetPreventGet("这个架子纹丝不动。");
}

int CanReceive(object ob) {
    if(ob->GetDamageType() != BLADE) {
        write("这是一个仅用于剑类武器的架子。");
        return 0;
    }
    else return 1;
}

void init(){
    ::init();
}
