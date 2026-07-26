#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("spider");
    SetAdjectives( ({"huge", "hairy"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一只巨大的蜘蛛");
    SetLong("这是一只巨大的毛蜘蛛，体型和家猫差不多。它看起来极其恶心，某种粘稠的液体正从它的口器中滴落。");
    SetMelee(1);
    SetLevel(1);
    SetRace("arachnid");
    SetClass("explorer");
    SetGender("male");
}
void init(){
    ::init();
}
