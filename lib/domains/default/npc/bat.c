#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("bat");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一只小蝙蝠");
    SetLong("一只普通的蝙蝠。它不比老鼠大多少。");
    SetWimpy(80);
    SetPermitLoad(1);
    SetPosition(POSITION_FLYING);
    SetWanderSpeed(1);
    SetLevel(1);
    SetMelee(1);
    SetRace("bat");
    SetMaxHealthPoints(20);
    SetGender("male");
    SetMessage("leave","$N scurries $D.");
}
void init(){
    ::init();
}
