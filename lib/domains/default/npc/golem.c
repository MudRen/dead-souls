#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("golem");
    SetAdjectives( ({"massive", "clay", "tall"}) );
    SetId( ({"clay man", "clayman", "klaymen", "emet"}) );
    SetShort("魔像埃梅特");
    SetLong("埃梅特是一个巨大的泥人，大约十英尺高，有着粗壮的手臂和腿。他的额头上写着一些神秘的符号。");
    SetLevel(10);
    SetMelee(1);
    SetRace("golem");
    SetGender("neuter");
}
void init(){
    ::init();
}
