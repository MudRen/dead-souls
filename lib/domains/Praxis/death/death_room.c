#include <lib.h>

inherit LIB_ROOM;

void create() {
    room::create();
    SetProperties(([ "light" : 3, "no magic" : 1 ]));
    SetShort("冥界");
    SetLong("这里将会变得更加有趣。出口在上面。");
    AddExit("up", "/domains/Praxis/square");
}
