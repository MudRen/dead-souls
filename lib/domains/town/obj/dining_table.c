#include <lib.h>

inherit LIB_BED;

void create() {
    ::create();
    SetKeyName("dining table");
    SetId( ({ "table" }) );
    SetAdjectives( ({ "very","long","dining","room","huge" }) );
    SetShort("一张很长的餐桌");
    SetLong("这是一张很长的餐桌，可容纳几十位客人。由精美的抛光木材制成。");
    SetMass(2000);
    SetBaseCost("silver",5000);
    SetMaxCarry(5000);
    inventory_visible();
    inventory_accessible();
    SetInventory( ([
                "/domains/town/obj/candlestick" : 2
                ]) );
}

mixed CanGet(object ob) { return "这张桌子太大太重了，你搬不走。"; }

void init(){
    ::init();
}
