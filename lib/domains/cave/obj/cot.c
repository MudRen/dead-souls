#include <lib.h>
#include <props.h>

inherit LIB_BED;

protected void create() {
    ::create();
    SetKeyName("cot");
    SetId( ({ "cot","bed" }) );
    SetAdjectives( ({ "simple"}) );
    SetShort("一张简易床");
    SetLong("这是一张简易床，适合那些不需要舒适床铺的人。");
    SetMass(500);
    SetBaseCost("silver",15);
    SetMaxSitters(2);
    SetMaxLiers(1);
}

void init(){
    ::init();
}
