#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("satyr");
    SetAdjectives( ({"wild", "ferocious", "looking", "male", "humanoid", "creature"}) );
    SetId( ({"male", "humanoid", "creature"}) );
    SetShort("一个 satyr");
    SetLong("这是一个 wild and ferocious looking humanoid male，上半身是 human，但下半身是 goatish, woolly，他的腿是 hooved animal 的。 Horns grow from beneath the wild mane of hair on his head。 However human his face might be， his expression and demeanor make it clear this is not a domesticated person， but an untamed forest creature。");
    SetLevel(1);
    SetMelee(1);
    SetRace("satyr");
    SetGender("male");
}
void init(){
    ::init();
}
