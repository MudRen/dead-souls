#include <daemons.h>
#include <lib.h>

inherit LIB_COMMAND;

int cmd(string str){
    object who = this_player();
    object env = environment(who);
    if(!env){
        write("没有环境。");
        return 1;
    }
    write("你随意挥了挥手，带来了和平。");
    say(who->GetCapName()+" waves "+possessive(who)+" hand "+
            "and brings peace to the area.");
    foreach(object combatant in get_livings(env)){
        if(combatant->GetInCombat()){
            tell_object(combatant,"You stop fighting.");
        }
        combatant->eventQuell();
    }
    return 1;
}

string GetHelp(string str) {
    return "Syntax: quell\n\n"
        "This command brings peace between combatants in your environment.\n"
        "See also: unquell";
}
