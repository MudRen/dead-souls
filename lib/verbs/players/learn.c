#include <lib.h>
#include <daemons.h>
#include <position.h>

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("learn");
    SetRules("","STR from LIV","to STR from LIV");
    SetErrorMessage("用法：learn <能力> from <人物>");
    SetHelp("Syntax: learn <ability> from <person>\n\n"
            "This command allows you to learn from another person "
            "an ability, spell, or skill.\nSee also: teach");
}

mixed can_learn_str_from_liv(string str, object ob){
    int pos = this_player()->GetPosition();
    if( this_player()->GetParalyzed() ) {
        return "你无法移动！";
    }
    if( pos == POSITION_LYING &&
            !RACES_D->GetLimblessCombatRace(this_player()->GetRace()) ){
        return "你当前的姿势无法学习！";
    }
    return 1;
}

mixed can_learn_to_str_from_liv(string str, object ob){
    return can_learn_str_from_liv(str, ob);
}

mixed can_learn(){
    return "用法：learn <%^BOLD%^%^CYAN%^能力%^RESET%^> from <%^BOLD%^%^ORANGE%^人物%^RESET%^>\n";
}

mixed do_learn_str_from_liv(string spell, object target){
    this_player()->eventLearn(target,spell);
    return 1;
}

mixed do_learn_to_str_from_liv(string spell, object target){
    return do_learn_str_from_liv(spell,target);
}
