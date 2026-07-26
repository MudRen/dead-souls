#include <lib.h>
#include <objects.h>

inherit  LIB_TRAINER;
void create(){
    trainer::create();
    SetKeyName("segata");
    SetId(({"segata", "sanshiro", "segata sanshiro"}));
    SetAdjectives(({"stocky","built","strong","strongly built"}));
    SetGender("male");
    SetRace("human");
    SetShort("�的場三四郎");
    SetLong("这位传奇武术大师体格健壮，帮助训练战士们成为最优秀的自己，"
            "以便他们能够履行自己的职责。"
            "的場三四郎专精于近战（徒手）搏斗。"
            "武器战斗训练请找公会长罗什德。");
    SetClass("fighter");
    SetLevel(40);
    AddTrainingSkills( ({ "melee attack", "melee defense" }) );
    SetSkill("melee attack", 100);
    SetSkill("melee defense", 100);
    SetPolyglot(1);
    SetLanguage("Common", 100);
    SetDefaultLanguage("Common");
    SetGuard("/domains/Ylsrim/obj/cask","Segata Sanshiro prevents your theft.");
    SetUnique(1);
}

void init() {
    trainer::init();
}
