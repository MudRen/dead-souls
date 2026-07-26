#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("any_hook", "", 1);
}

void create() {
    ::create();
    SetNoClean(1);
    SetShort("上锁的房间");
    SetProperties(([ "no scry" : 1, "light" : 1, "indoors" : 1 ]));
    SetLong(
            "你已被同化。\n"
            "从现在起，你将为博格服务。");
    SetExits( 
            (["square" : "/domains/Praxis/square"]) );
}

protected int any_hook(string str) {
    message("prompt", sprintf("\n(%s) Password: ", mud_name()),
            this_player());
    return 1;
}
int CanReceive(object ob) {
    if(!ob) ob = previous_object();
    if(!(ob->query_locked())) return 0;
    else return ::CanReceive(ob);
}
