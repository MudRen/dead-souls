#include <lib.h>
#include <daemons.h>
#include <position.h>

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("teach");
    SetRules("","STR to LIV","LIV to STR");
    SetErrorMessage("用法：teach <能力> to <人物>");
    SetHelp("Syntax: teach <ability> to <person>\n\n"
            "This command allows you to teach another person "
            "an ability, spell, or skill.\nSee also: learn");
}

mixed can_teach_str_to_liv(string str, object ob){
    int pos = this_player()->GetPosition();
    if( this_player()->GetParalyzed() ) {
        return "你无法移动！";
    }
    if( pos == POSITION_SITTING || pos == POSITION_LYING &&
            !RACES_D->GetLimblessCombatRace(this_player()->GetRace()) ){
        return "你当前的姿势无法教学！";
    }
    return 1;
}

mixed can_teach_liv_to_str(object ob, string str){
    return can_teach_str_to_liv(str, ob);
}

mixed can_teach(){
    return "用法：teach <%^BOLD%^%^CYAN%^能力%^RESET%^> to "
        "<%^BOLD%^%^ORANGE%^人物%^RESET%^>";
}

mixed do_teach_str_to_liv(string spell, object target){
    this_player()->eventOfferTeaching(target,spell);
    return 1;
}

mixed do_teach_liv_to_str(object target, string spell){
    return do_teach_str_to_liv(spell,target);
}
