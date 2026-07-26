#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int eventNoob(){
    write("%^RED%^新玩家须知\n%^RESET%^");
    this_player()->eventPage("/doc/help/players/handbook");
    return 1;
}

mixed cmd(string str) {
    return eventNoob();
}

string GetHelp() {
    eventNoob();
}

