/*  Allows players to possibly help a target follow.
 *  created by Rush@Dead Souls
 */

#include <lib.h>
#include "include/lead.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("lead");
    SetRules("LIV");
    SetErrorMessage("你想带领谁？");
    SetHelp("Syntax: lead <LIVING>\n\n"    
            "Allows one to assist a living being who is "
            "attempting to follow.\n"
            "See also: evade, follow, tracking, stealth\n");
}

mixed can_lead_liv() { return 1; }

mixed do_lead_liv(object ob) {
    if(!ob->IsFollowing(this_player())) {
        this_player()->eventPrint(ob->GetName() + "没有跟随你。");
        return 1;
    }
    if( this_player()->SetFollowed(ob, 1) ) {
        ob->eventPrint(this_player()->GetName() + "现在正在带领你。");
        this_player()->eventPrint("你现在正在带领" + ob->GetName() + "。");
    }
    else this_player()->eventPrint("你无权带领" + ob->GetName() + "。");
    return 1;
}
