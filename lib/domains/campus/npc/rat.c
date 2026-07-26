#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("a mangy little rat");
    SetId(({"rat","dirty rat"}));
    SetShort("一只老鼠");
    SetLong("一只邋遢的小脏老鼠。");
    SetLevel(1);
    SetMaxHealthPoints(5);
    SetRace("rodent");
    SetGender("male");
    SetWanderSpeed(1);
    SetMessage("come","$N scurries in.");
    SetMessage("leave","$N scurries $D.");
    SetAction(5, ({ 
                "The rat squeaks.", "You hear a rat scuttling about.", 
                "A scruffy little rat brushes against your leg.",
                "You hear tiny munching sounds."}));
}
void init(){
    ::init();
}
