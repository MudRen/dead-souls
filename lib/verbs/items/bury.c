/*    /verbs/items/bury.c
 *    From the Dead Souls Mud Library
 *    Buries objects where no one can find them
 *    Created by Descartes of Borg 951030
 */

#include <lib.h>
#include <rounds.h>
#include <position.h>

inherit LIB_VERB;

protected void eventBury(object who, object tool, object what, object check) {
    if( !who || environment(who) != check ) {
        return;
    }
    if( !tool || (environment(tool) != who) ) {
        who->eventPrint("你失去了你的挖掘装备。");
        return;
    }
    tool->eventBuryWith(who, what);
}

varargs protected void eventPrepareBury(object who, object tool, object what) {
    function f = (: eventBury($(who), $(tool), $(what),environment($(who))) :);

    if( who->GetInCombat() ) {
        send_messages("start", "$agent_name $agent_verb 用" +
                tool->GetShort() + "掩埋。", who, 0,
                environment(who));
        who->SetAttack(0, f, ROUND_OTHER);
    }
    else {
        evaluate(f);
    }
}

protected void create() {
    verb::create();
    SetVerb("bury");
    SetErrorMessage("用什么埋什么？");
    SetRules("OBJ with OBJ", "STR with OBJ");
    SetHelp("Syntax: <bury ITEM with TOOL>\n\n"
            "Allows you to use a digging tool to bury things.\n\n"
            "See also: dig");
}

mixed can_bury_str_with_obj() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了！";
    }
    if( this_player()->GetPosition() != POSITION_STANDING ) {
        return "你只能站着时埋东西！";
    }
    return this_player()->CanManipulate();
}

mixed can_bury_obj_with_obj() {
    return can_bury_str_with_obj();
}

mixed do_bury_str_with_obj(string str, object tool) {
    eventPrepareBury(this_player(), tool);
    return this_player()->CanManipulate();
}

mixed do_bury_obj_with_obj(object what, object tool) {
    eventPrepareBury(this_player(), tool, what);
    return 1;
}
