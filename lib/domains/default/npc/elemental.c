#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("elemental");
    SetId( ({"transcendental", "manifestation"}) );
    SetAdjectives( ({"boredom"}) );
    SetShort("一个无聊元素");
    SetLong("通常元素是由土、水、风或火四种元素之一组成的召唤生物。这个奇异的显现似乎不属于其中任何一种，实际上似乎是出于一种纯粹的、超越性的无聊而自行凝聚而成的。也许，它更像是一个无聊的超验体。");
    SetLevel(1);
    SetMelee(1);
    SetRace("elemental");
    SetGender("neuter");
}
void init(){
    ::init();
}
