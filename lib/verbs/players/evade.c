/*  Allows players to possibly evade a targets
 *  created by Rush@Dead Souls
 */

#include <lib.h>
#include "include/evade.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("evade");
    SetRules("LIV");
    SetErrorMessage("你想躲避谁？");
    SetHelp("Syntax: evade <LIVING>\n\n"
            "Allows one to attempt to evade a living being "
            "who is currently following.\n"
            "See also: follow, lead, tracking, stealth\n");
}

mixed can_evade_liv() { return 1; }

mixed do_evade_liv(object ob) {
    if(!this_player()->SetAllowed(ob, 0)){
        this_player()->eventPrint("你现在正在躲避" + 
                ob->GetName() + "。");
    }
    else this_player()->eventPrint("你无权躲避" + ob->GetName() + "。");
    return 1;
}
