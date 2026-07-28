/*    /verbs/items/pick.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951220
 *    Version: @(#) pick.c 1.4@(#)
 *    Last modified: 96/10/15
 */

#include <lib.h>
#include <rounds.h>
#include "include/pick.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("pick");
    SetRules("STR on OBJ", "STR on OBJ with OBJ", "OBJ");
    SetErrorMessage("你可以摘花，或者撬开...的锁。");
    SetHelp("Syntax: <pick OBJECT>\n"
            "        <pick lock on OBJECT>\n"
            "        <pick lock on OBJECT with TOOL>\n\n"
            "Depending on what you are doing, this command captures two "
            "different senses of the verb \"pick\".  In the first sense, "
            "<pick OBJECT>, pick allows you to pick things like flowers or "
            "strawberries (not your nose).\n\n"
            "The second conext allows you to open locked things without a key.  "
            "Some tools can help you stealthfully pick a lock, while "
            "others may help you pick it through brute force.\n\n"
            "See also: close, lock, open, unlock");
}

mixed can_pick_obj() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

mixed can_pick_str_on_obj(string str) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    if( this_player()->GetStaminaPoints() < 20 ) {
        return "你太累了。";
    }
    return this_player()->CanManipulate();
}

mixed can_pick_str_on_obj_with_obj(string str) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    if( this_player()->GetStaminaPoints() < 30 ) {
        return "你太累了。";
    }
    return this_player()->CanManipulate();
}

mixed do_pick_obj(object ob, string id) {
    return ob->eventPickItem(this_player(), remove_article(lower_case(id)));
}

mixed do_pick_str_on_obj(string wrd, object ob, mixed *args...) {
    wrd = remove_article(lower_case(args[1]));
    this_player()->eventPrint("你审视着锁的弱点。");
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: $(ob)->eventPick(this_player(), $(wrd)):),
                ROUND_OTHER);
    else ob->eventPick(this_player(), wrd);
    return 1;
}

mixed do_pick_str_on_obj_with_obj(string wrd, object ob, object tool,
        mixed *args...) {
    wrd = remove_article(lower_case(args[1]));
    this_player()->eventPrint("你审视着锁的弱点。");
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: $(ob)->eventPick(this_player(), $(wrd),
                        $(tool)) :),ROUND_OTHER);
    else ob->eventPick(this_player(), wrd, tool);
    return 1;
}
