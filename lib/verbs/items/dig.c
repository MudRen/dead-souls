/*    /verbs/items/dig.c
 *    From the Dead Souls Mud Library
 *    Verb for digging things
 *    Created by Descartes of Borg 951030
 *    Version: @(#) dig.c 1.2@(#)
 *    Last modified: 97/01/01
 */

#include <lib.h>
#include <rounds.h>
#include <position.h>

inherit LIB_VERB;

protected void eventDig(object who, object tool, object what, object check) {
    if( !who || check != environment(who) ) {
        return;
    }
    if( !tool || (environment(tool) != who) ) {
        who->eventPrint("你失去了你的装备。");
        return;
    }
    tool->eventDigWith(who, what);
}

varargs protected void eventPrepareDig(object who, object tool, object what) {
    function f = (: eventDig($(who), $(tool), $(what), environment($(who))) :);

    if( this_player()->GetInCombat() ) {
        send_messages("start", "$agent_name $agent_verb 用" +
                tool->GetShort() + "挖掘。", who, 0, environment(who));
        who->SetAttack(0, f, ROUND_OTHER);
    }
    else {
        evaluate(f);
    }
}

protected void create() {
    verb::create();
    SetVerb("dig");
    SetRules("with OBJ", "STR with OBJ", "OBJ with OBJ");
    SetErrorMessage("用什么挖？有什么特别要挖的吗？");
    SetHelp("Syntax: <dig with TOOL>\n"
            "        <dig THING with TOOL>\n\n"
            "Allows you to dig with digging tools.  Sometimes you may "
            "be required to specify what it is you wish to dig.  In "
            "that case, you can use the thing field to specify what it is "
            "you wish to dig.\n\n"
            "See also: bury");
}

mixed can_dig_with_obj() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了！";
    }
    if( this_player()->GetPosition() != POSITION_STANDING ) {
        return "你没站着怎么挖？";
    }
    return this_player()->CanManipulate();
}

mixed can_dig_str_with_obj() {
    return can_dig_with_obj();
}

mixed can_dig_obj_with_obj() {
    return can_dig_with_obj();
}

mixed do_dig_with_obj(object ob) {
    eventPrepareDig(this_player(), ob);
    return 1;
}

mixed do_dig_str_with_obj(string str, object ob) {
    if( remove_article(lower_case(str)) != "hole" ) {
        return 0;
    }
    return do_dig_with_obj(ob);
}

mixed do_dig_obj_with_obj(object what, object ob, string id) {
    eventPrepareDig(this_player(), ob, what);
    return 1;
}
