#include <lib.h>

inherit LIB_NPC;

void check_quest(string *what);
void check_immortal(string a, string b);

void create() {
    ::create();
    SetKeyName("unity");
    SetId(  ({ "unity" }) );
    SetShort( "尤尼提，不朽的授予者");
    SetAggressive( 0);
    SetLevel(28);
    SetLong( "尤尼提为那些有导师赞助的高级凡人授予不朽。");
    SetMorality(1000);
    SetRace( "human");
    SetMaxHealthPoints(100000);
    SetHealthPoints(100000);
    SetRace("human");
}

void catch_tell(string str) {
    object ob;
    string a, b, c;

    if(this_player() == (ob = this_object())) return;
    if(sscanf(str, "%squest%s", a, b) == 2 || sscanf(str, "%stask%s", a, b) == 2) {
        this_object()->eventForce("speak in farsi 你必须为我找到兽人杀手！邪恶的兽人把它夺走了，以免它被用来对付他们。普拉克西斯的人民必须把它拿回来。");
        return;
    }
    if(sscanf(str, "%shere%slayer%s", a, b, c) == 3) {
        this_object()->eventForce("speak in farsi 兽人杀手在兽人山谷的宝库里。");
        return;
    }
    if(sscanf(str, "%s gives you %s", a, b) == 2) {
        call_out("check_quest", 2, ({ lower_case(a), lower_case(b) }) );
    }
}

void check_quest( string *what ) {
    object tp, ob;
    string who, that;

    who = what[0];
    that = what[1];
    tp = present(who, environment(this_object()));
    ob = present("sword");
    if(!tp) return;
    if(!ob) {
        tell_object(tp, "尤尼提说：不错的尝试。现在离开，否则死。");
        return;
    }
    if(!ob->id("the_one_orc_slayer")) {
        tell_object(ob, "尤尼提说：这很好，但我不需要它。");
        eventForce("give "+that+" to "+who);
        return;
    }
    tell_room(environment(this_object()), "尤尼提开心地笑了。", this_object());
    tell_room(environment(this_object()), tp->query_cap_name()+"完成了兽人杀手的任务。", ({ tp, this_object() }));
    tell_object(tp, "尤尼提说：你做得很好。总有一天你会成为高级凡人！");
    ob->destruct();
    if(tp->set_quest("orcslayer")) tp->add_exp(1000);
}
