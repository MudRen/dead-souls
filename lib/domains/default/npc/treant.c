#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("treant");
    SetAdjectives( ({"great", "old", "giant", "ancient", "benevolent"}) );
    SetId( ({"protector", "tree"}) );
    SetShort("一个古老的树人");
    SetLong("这是一个伟大的古老树人，看起来很像一棵有脸、手臂和腿的巨树。作为森林的古老守护者，树人因其普遍的善意和仁慈而受到广泛尊敬。");
    SetLevel(1);
    SetMelee(1);
    SetRace("tree");
    SetGender("neuter");
}
void init(){
    ::init();
}
