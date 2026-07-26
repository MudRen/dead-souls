#include <lib.h>

inherit LIB_BED;

void create() {
    ::create();
    SetKeyName("pool table");
    SetId( ({ "table" ,"billiards table"}) );
    SetAdjectives( ({ "billiard", "wood","wooden", "pool", "billiards" "large" }) );
    SetShort("一张台球桌");
    SetLong("这是一张用深色重木制成的大桌子。桌面覆盖着绿色毛毡，角落和侧面有六个洞，球可以穿过。");
    SetMass(10000);
    SetBaseCost("silver",1200);
    SetMaxCarry(5000);
    inventory_visible();
    inventory_accessible();
    SetInventory( ([
                "/domains/town/weap/cue" : 2,
                "/domains/town/obj/pool_ball" : 16,
                ]) );
}
void init(){
    ::init();
}
