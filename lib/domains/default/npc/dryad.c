#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("dryad");
    SetAdjectives( ({"tree hugging", "tree-hugging", "hippie"}) );
    SetId( ({"hippie"}) );
    SetShort("一个抱树嬉皮士");
    SetLong("仔细一看，这不只是个嬉皮士女孩。这是一个货真价实的树灵，显然是迷路了才会在这里闲逛。");
    SetLevel(1);
    SetMelee(1);
    SetRace("dryad");
    SetGender("female");
}
void init(){
    ::init();
}
