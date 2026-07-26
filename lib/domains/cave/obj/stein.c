#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("grog stein");
    SetId( ({"stein", "mug"}) );
    SetAdjectives( ({"grog","fancy"}) );
    SetShort("一个啤酒杯");
    SetLong("一个可以装很多酒的大杯子，非常精美，无疑价值不菲。");
    SetMass(30);
    SetBaseCost("silver",300);
    SetVendorType(VT_TREASURE);
    SetFlaskUses(0);
    SetStrength(5);
    SetMaxFlask(10); 
    SetMealType(MEAL_DRINK);
    SetPreventGet("Oddly, it appears extremely difficult to reach.");
}

void init(){
    ::init();
}
