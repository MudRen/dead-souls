#include <lib.h>
#include <props.h>

inherit LIB_BED;
inherit LIB_SMELL;


protected void create() {
    ::create();
    SetKeyName("metal cot");
    SetId( ({ "cot","bed" }) );
    SetAdjectives( ({ "simple","metal" }) );
    SetShort("一张简易小床");
    SetLong("这是一张简易金属小床，设计用于在营地中临时休息使用。");
    SetMass(50);
    SetBaseCost("silver",15);
    SetMaxSitters(2);
    SetMaxLiers(1);
}

mixed CanGet(object ob) { return "行军床固定在地上。";}

void init(){
    ::init();
}
