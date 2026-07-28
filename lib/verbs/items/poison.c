/*  /verbs/items/poison.c
 *  from the Dead Souls  Library
 *  poison
 *  poison OBJ with OBJ
 *  created by Blitz@Dead Souls 951020
 *  a check for poison uses put in by BillGates 961202
 */



#include <lib.h>
#include <rounds.h>
#include "include/poison.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("poison");
    SetRules("OBJ with OBJ");
    SetErrorMessage("用什么毒害什么？");
    SetHelp("Syntax: <poison ITEM with POISON>\n\n"
            "This command allows you to poison items, provided you "
            "have a poisoning agent, and something to poison.  The "
            "ITEM is the item which you want to poison.  The "
            "POISON is what you wish to use to poison it with.");
}

mixed can_poison_obj_with_obj(string verb) { return this_player()->CanManipulate(); }

mixed do_poison_obj_with_obj(object target, object agent) {
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventPoison, this_player(), target,
                    agent :), ROUND_OTHER);
    else eventPoison(this_player(), target, agent);
    return 1;
}

void eventPoison(object who, object target, object agent) {
    if( !who ) return;
    if( environment(agent) != this_player() ) {
        who->eventPrint("你不再有毒药了。");
        return;
    }
    if( !(agent->GetPoisonUses()) ) {
        who->eventPrint("你的毒药已经用完了。");
        return;
    }
    agent->eventSpreadPoison(who, target);
}
