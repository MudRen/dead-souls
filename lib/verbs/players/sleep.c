#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("sleep");
    SetRules("");
    SetErrorMessage("睡觉？");
    SetSynonyms("go to sleep");
    SetHelp("用法：sleep\n"
            "如果躺着，你会入睡。如果不是躺着，你会倒下睡着。"
            "被攻击通常会唤醒你，否则你将在几分钟后醒来，"
            "变得更加精力充沛。");
}

mixed can_sleep() {
    if( !creatorp(this_player()) && this_player()->GetCaffeine() > 10 ) {
        return "你现在太兴奋了，睡不着。";
    }
    if(this_player()->GetRace()=="elf") return "精灵不需要睡觉。";

    return 1;
}

mixed do_sleep() {
    tell_player(this_player(),"你睡着了。");
    tell_room(environment(this_player()), this_player()->GetName()+
            "闭上"+possessive(this_player())+"眼睛，似乎失去了意识。", ({this_player()}) );
    return this_player()->SetSleeping(random(10)+5);
}
