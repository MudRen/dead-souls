#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("horse");
    SetId(({"horse","large horse","hands","quadruped","ungulate"}));
    SetAdjectives(({"large","hooved","mr","mister"}));
    SetShort("一匹大马");
    SetLong("一匹大型有蹄四足动物，比你更高更壮。也许如果你和它交朋友，它会允许你骑上它。");
    SetNoClean(1);
    SetWimpy(50);
    SetLevel(5);
    SetRace("horse");
    SetGender("male");
    SetMelee(1);
    //SetAction(5, ({ 
    //	"The horse snorts.", "You hear the horse whinny.", 
    //	"The horse flips its tail in the air.",
    //	"The horse looks around."}));
    SetMount(1);
    SetCanBefriend(1);
}
void init(){
    ::init();
}
