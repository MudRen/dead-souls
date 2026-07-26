#include <lib.h>
#include <objects.h>

inherit LIB_TRAINER;
void create(){
    trainer::create();
    SetKeyName("radagast");
    SetId("radagast the brown","wizard","mage","trainer");
    SetAdjectives(({"friendly","tall","thin","old"}));
    SetGender("male");
    SetRace("human");
    SetNoSpells(1);
    SetShort("褐袍拉达加斯特");
    SetLong("这是一个高瘦的老人。人们对这位神秘的巫师知之甚少，"+
            "只知道他对动物有着传奇般的仁慈，以及他作为煽动性叛乱者的争议名声。"+
            "他可以训练你魔法防御、魔法攻击和召唤术。"+
            "例如，你可以\"ask radagast to train conjuring\"。"+
            "如果你缺少训练点数，那就去冒险并从德克那里获得晋升。"+
            "升级后你会获得训练点数。"); 
    SetClass("mage");
    SetLevel(40);
    AddTrainingSkills( ({ "magic defense", "magic attack", "conjuring" }) );
    SetSpellBook( ([ "buffer" : 100, "meditate" : 100, "missile" : 100, "fireball" : 100 ]) );
    SetPolyglot(1);
    SetCustomXP(10);
}

void init() {
    trainer::init();
    SetSmell(([  "default" : "一股相当奇怪的霉味。"]));
    SetListen(([  "default" : "拉达加斯特似乎在不停地"+
                "低声哼着小曲。"]));
}

int eventHelp(object who, string unused){
    ::eventHelp(who);
    this_object()->eventForce("speak 请注意我只懂"+
            "英语。如果你用其他语言和我说话，我"+
            "听不懂！");
    return 1;
}
