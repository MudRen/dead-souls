#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("elemental");
    SetId( ({"transcendental", "manifestation"}) );
    SetAdjectives( ({"boredom"}) );
    SetShort("一个无聊元素");
    SetLong("通常元素是由 earth、water、wind 或 fire 四种元素之一组成的 summoned creatures。这个 bizarre manifestation appears to be none of those， and in fact seems to have coalesced unbidden out of a sheer, transcendent boredom。 It is, perhaps, more of a boredom transcendental。");
    SetLevel(1);
    SetMelee(1);
    SetRace("elemental");
    SetGender("neuter");
}
void init(){
    ::init();
}
