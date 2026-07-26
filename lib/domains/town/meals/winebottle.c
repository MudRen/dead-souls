#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("bottle");
    SetId( ({"vessel","winebottle","bottle of wine","nouveau"}) );
    SetAdjectives( ({"wine","glass","nouveau"}) );
    SetShort("一瓶葡萄酒");
    SetLong("一瓶什么什么新酒。标签太脏了看不清。");
    SetMass(40);
    SetBaseCost("gold",2);
    SetVendorType(VT_DRINK);
    SetFlaskContents("wine");
    SetFlaskUses(10);
    SetStrength(20);
    SetMaxFlask(10); 
    SetMealType(MEAL_ALCOHOL);
    SetItems(([
                "label" : "It is attached to the bottle and is meant to be read.",
                ]));
    SetReads(([
                "label" : "It's too stained to read, all right.",
                ]));
}
void init(){
    ::init();
}
