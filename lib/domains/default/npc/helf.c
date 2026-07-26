#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("optis");
    SetId( ({"half elf", "half-elf", "half-human", "half human"}) );
    SetAdjectives(({"non-player", "non player"}));
    SetShort("半精灵奥普蒂斯");
    SetLong("像他的大多数同类一样，奥普蒂斯非常迷人且健壮。他的耳朵不是完全尖的，但他足够异域风情，在女士们中很受欢迎。");
    SetLevel(1);
    SetMelee(1);
    SetRace("half-elf");
    SetGender("male");
}
void init(){
    ::init();
}
