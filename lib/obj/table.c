#include <lib.h>

inherit LIB_TABLE;


void create() {
    ::create();
    SetKeyName("generic table");
    SetId( ({ "table","surface" }) );
    SetAdjectives( ({ "generic"}) );
    SetShort("普通桌子");
    SetLong("这是一个可以放置物品的平面。");
    SetBaseCost("silver",1);
    SetMaxCarry(500);

}
void init(){
    ::init();
}
