#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("cup");
    SetId( ({"cup", "trophy"}) );
    SetAdjectives( ({"trophy", "brass", "small"}) );
    SetShort("一个小奖杯");
    SetLong("大约茶杯大小，这个黄铜杯看起来像是某种比赛的奖杯。上面刻着字。");
    SetItems(([
                ({ "word", "words", "engraving", "inscription" }) : "Words engraved on the cup.",
                ]));
    SetRead(([
                "default" : "Try: read inscription on cup",
                ({ "word", "words", "inscription", "engraving" }) : "3rd Runner Up, Junior Miss Cocoa Butter Pageant, 1963",
                ]));
    SetMass(10);
    SetBaseCost("silver",100);
    SetVendorType(VT_TREASURE);
    SetFlaskUses(0);
    SetStrength(5);
    SetMaxFlask(1); 
    SetMealType(MEAL_DRINK);
}

void init(){
    ::init();
}
