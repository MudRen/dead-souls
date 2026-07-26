#include <lib.h>
#include <size_types.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("spider");
    SetAdjectives( ({"huge", "hairy"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一只巨大的蜘蛛");
    SetLong("这是一只巨大的毛蜘蛛，大约有家猫那么大。它看起来 absolutely vile，某种粘稠的液体正从它的口器中滴落。");
    SetWimpy(80);
    SetMelee(1);
    SetLevel(1);
    SetRace("arachnid");
    SetClass("explorer");
    SetGender("male");
}
void init(){
    ::init();
}
