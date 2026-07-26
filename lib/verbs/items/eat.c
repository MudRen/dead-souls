/*    /verbs/items/eat.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951113
 *    Version: @(#) eat.c 1.3@(#)
 *    Last modified: 96/11/03
 */



#include <lib.h>
#include <rounds.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("eat");
    SetSynonyms("swallow");
    SetErrorMessage("吃什么？");
    SetRules("OBJ");
    SetHelp("用法：eat <食物>\n\n"
            "允许你吃一些食物。保持饱食状态有助于你更快地恢复伤口并拥有更大的耐力。\n\n"
            "另见：bait, cast, drink, fish");
}


void eventEat(object who, object what) {
    if( !what ) {
        return;
    }
    return what->eventEat(who);
}

mixed can_eat_obj() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

mixed do_eat_obj(object ob) {
    if( this_player()->GetInCombat() ) {
        this_player()->SetAttack(0, (: eventEat, this_player(), ob :),
                ROUND_OTHER);
    }
    else {
        eventEat(this_player(), ob);
    }
    return 1;
}
