/*    /verbs/players/pray.c
 *    From Dead Souls LPMud
 *    Created by Descartes of Borg 961101
 *    Version: @(#) pray.c 1.3@(#)
 *    Last modified: 96/11/03
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("pray");
    SetRules("for STR", "for STR against STR", "for STR against STR for LIV",
            "for STR for OBJ");
    SetErrorMessage("祈祷什么？");
    SetHelp("用法：pray for <祈祷>\n"
            "      pray for <祈祷> against <某物>\n"
            "      pray for <祈祷> against <某物> for <某人>\n\n"
            "允许你向你信仰的神明祈祷。\n"
            "另见：prayers");
}

mixed parse_spell(string spell){
    string s1, s2;
    int ret;
    object target;
    if(query_verb() == "cast") return ({ "cast" });
    ret = sscanf(spell,"%s against %s",s1, s2);
    if(ret != 2) ret = sscanf(spell,"%s for %s",s1, s2);
    if(ret != 2) s1 = spell;
    if(s2){
        target = get_object(s2);
    }
    return ({ s1, ( target || s2 ) });
}

mixed can_pray_for_str(string spell) {
    object tmp;
    string *tmpstr = parse_spell(spell);
    tmp = SPELLS_D->GetSpell(spell);
    if(!tmp) tmp = SPELLS_D->GetSpell(tmpstr[0]);

    if(!tmp){
        return 0;
    }

    if( tmp ) {
        string verb = tmp->GetVerb();
        if( verb != "pray" ) {
            return "那不是你祈祷的东西。";
        }
    }
    return this_player()->CanCast(tmp);
}

mixed can_pray_for_str_against_str(string spell) {
    return can_pray_for_str(spell);
}

mixed can_pray_for_str_for_obj(string spell) {
    return can_pray_for_str(spell);
}

mixed can_pray_for_str_against_str_for_liv(string spell) {
    return can_pray_for_str(spell);
}

mixed do_pray_for_str(string spell) {
    mixed foo = parse_spell(spell);
    if(sizeof(foo) == 2 && foo[1])
        return this_player()->eventPrepareCast(foo[0], foo[1]);
    else return this_player()->eventPrepareCast(foo[0]);
}

mixed do_pray_for_str_against_str(string spell, string ag) {
    return this_player()->eventPrepareCast(spell, ag);
}

mixed do_pray_for_str_for_obj(string spell, object ob) {
    return this_player()->eventPrepareCast(spell, ob);
}

mixed do_pray_for_str_against_str_for_liv(string spell, string ag, object tg) {
    return this_player()->eventPrepareCast(spell, ag, tg);
}
