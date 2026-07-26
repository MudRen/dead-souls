#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("triffid");
    SetAdjectives( ({"six foot tall", "six feet tall", "thick", "bushy", "thorned", "menacing"}) );
    SetId( ({"plant"}) );
    SetShort("一株高大的植物");
    SetLong("这种植物大约六英尺高，类似于一种非常粗壮茂密的玉米植物。它拥有触手般的带刺藤蔓，威胁地挥舞着，看起来能够移动。");
    SetLevel(1);
    SetMelee(1);
    SetRace("plant");
    SetGender("neuter");
}
void init(){
    ::init();
}
