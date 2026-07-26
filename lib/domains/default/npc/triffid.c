#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("triffid");
    SetAdjectives( ({"six foot tall", "six feet tall", "thick", "bushy", "thorned", "menacing"}) );
    SetId( ({"plant"}) );
    SetShort("一株高大的植物");
    SetLong("这种植物大约六英尺高， similar to a very thick and bushy corn plant。它 possesses tentacle-like thorned vines which wave about menacingly， and it appears capable of locomotion。");
    SetLevel(1);
    SetMelee(1);
    SetRace("plant");
    SetGender("neuter");
}
void init(){
    ::init();
}
