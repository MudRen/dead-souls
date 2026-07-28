#include <daemons.h>
#include <lib.h>

inherit LIB_COMMAND;

int cmd(string str){
    write("你打了个响指，允许战斗继续进行。");
    say(this_player()->GetCapName()+" snaps "+possessive()+" fingers "+
            "and permits hostilities to resume.");
    foreach(object combatant in get_livings(environment(this_player()))){
        combatant->eventUnQuell();
        if(combatant->GetInCombat()) tell_object(combatant,"你恢复了战斗。");
    }

    return 1;
}

string GetHelp(){
    return "语法：unquell\n\n"
        "允许被停止的战斗恢复进行。\n"
        "另见：quell";
}
