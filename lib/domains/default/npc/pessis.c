#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("pessis");
    SetId( ({"half-orc", "half orc", "half human", "half-human"}) );
    SetAdjectives(({"non-player", "non player"}));
    SetShort("半兽人佩西斯");
    SetLong("长相太过粗犷野蛮，算不上英俊的人类；又太过纤细，称不上合格的兽人。佩西斯一生都活在屈辱和排斥之中。可以理解他对这个话题有些敏感，所以最好不要提起这件事。");
    SetInventory(([
                "/domains/default/armor/horc_shirt" : "wear tshirt",
                ]));
    SetLevel(1);
    SetMelee(1);
    SetRace("half-orc");
    SetGender("male");
}
void init(){
    ::init();
}
