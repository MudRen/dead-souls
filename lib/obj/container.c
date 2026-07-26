#include <lib.h>

inherit LIB_STORAGE;


void create() {
    ::create();
    SetKeyName("container");
    SetId( ({ "container" }) );
    SetAdjectives( ({ "generic","nondescript" }) );
    SetShort("普通容器");
    SetLong("这是一个可以容纳其他物品的容器。");
    SetCanClose(1);
    SetMass(274);
    SetBaseCost("silver",1);
    SetMaxCarry(500);
}
void init(){
    ::init();
}
