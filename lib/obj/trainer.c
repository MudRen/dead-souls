#include <lib.h>

inherit  LIB_TRAINER;
void create(){
    trainer::create();
    SetKeyName("trainer");
    SetId("generic trainer");
    SetGender("male");
    SetRace("human");
    SetShort("普通训练师");
    SetLong("这是一个教你技能的人。"+
            "例如，'ask trainer to teach wibbling'会让他开始教你wibbling技能，"+
            "前提是他会这项技能，并且你有足够的训练点数。"+
            "如果你缺少训练点数，那就去冒险升级吧。"+
            "升级后你将获得训练点数。");
    SetLevel(1);
    AddTrainingSkills( ({"wibbling"}));
}
void init() {
    ::init();
}
