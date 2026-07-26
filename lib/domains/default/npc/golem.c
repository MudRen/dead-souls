#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("golem");
    SetAdjectives( ({"massive", "clay", "tall"}) );
    SetId( ({"clay man", "clayman", "klaymen", "emet"}) );
    SetShort("魔像埃梅特");
    SetLong("埃梅特是一个 massive clay man， some ten feet tall and with great, thick arms and legs。 Written on his forehead are some cryptic glyphs。");
    SetLevel(10);
    SetMelee(1);
    SetRace("golem");
    SetGender("neuter");
}
void init(){
    ::init();
}
