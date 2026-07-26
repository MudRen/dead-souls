/*    /verbs/players/cast.c
 *    From Dead Souls LPMud
 *    Created by Descartes of Borg 951027
 *    Version: @(#) cast.c 1.4@(#)
 *    Last modified: 96/12/16
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("cast");
    SetRules("STR", "STR on OBJ", "STR on STR", "STR on STR of OBJ",
            "STR against STR");
    SetErrorMessage("施放什么法术？对谁施放？");
    SetHelp("用法：cast <法术>\n"
            "      cast <法术> on <肢体>\n"
            "      cast <法术> against <字符串>\n"
            "      cast <法术> on <目标>\n"
            "      cast <法术> on <肢体> of <目标>\n\n"
            "允许你使用法术所需的任何语法来施放法术。例如，要治疗某人，"
            "可以输入 \"cast heal on descartes\"。");
}

mixed can_cast_str(string spell) {
    object tmp = SPELLS_D->GetSpell(spell);

    if( tmp ) {
        string verb = tmp->GetVerb();

        if( verb != "cast" ) {
            return "那不是你施放的法术。";
        }
    }
    if(intp(this_player()->CanManipulate())) return this_player()->CanCast(tmp);
}

mixed can_cast_str_on_obj(string spell) {
    return can_cast_str(spell);
}

mixed can_cast_str_on_str(string spell) {
    return can_cast_str(spell);
}

mixed can_cast_str_against_str(string spell) {
    return can_cast_str(spell);
}

mixed can_cast_str_on_str_of_str(string spell) {
    return can_cast_str(spell);
}

mixed do_cast_str(string spell) {
    return this_player()->eventPrepareCast(spell);
}

mixed do_cast_str_on_obj(string spell, object target) {
    return this_player()->eventPrepareCast(spell, target);
}

mixed do_cast_str_against_str(string spell, object target) {
    return this_player()->eventPrepareCast(spell, target);
}

mixed do_cast_str_on_str(string spell, string limb) {
    return this_player()->eventPrepareCast(spell, limb);
}

mixed do_cast_str_on_str_of_obj(string spell, string limb, object target) {
    return this_player()->eventPrepareCast(spell, limb, target);
}
