#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("dryad");
    SetAdjectives( ({"tree hugging", "tree-hugging", "hippie"}) );
    SetId( ({"hippie"}) );
    SetShort("一个抱树嬉皮士");
    SetLong("仔细一看，这不只是个嬉皮士 chick。这是一个 honest-to-goodness tree spirit， evidently a bit lost to be hanging around here。");
    SetLevel(1);
    SetMelee(1);
    SetRace("dryad");
    SetGender("female");
}
void init(){
    ::init();
}
