#include <lib.h>
#include "../customdefs.h"

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("case");
    SetId( ({ "container" }) );
    SetAdjectives( ({ "generic","nondescript" }) );
    SetShort("一个玻璃展示柜");
    SetLong("这是一个看起来价格不菲、装饰华丽的玻璃展示柜。看起来非常适合存放奖杯或珠宝用于展示。这是一个透明容器的示例。");
    SetInventory(([
                MY_AREA "/obj/watch" : 1,
                ]));
    SetOpacity(10);
    SetCanClose(1);
    SetClosed(1);
    SetMass(274);
    SetBaseCost("silver",1);
    SetMaxCarry(500);
}
void init(){
    ::init();
}

mixed CanGet(object ob) { return "The case does not budge.";}
