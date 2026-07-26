#include <lib.h>
inherit LIB_CHAPEL;

protected void create() {
    chapel::create();
    SetTown("town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("镇书记官办公室");
    SetLong("这间小办公室是人们办理公务的地方。市政厅的主厅在南边。");
    SetProperties (([
                "no attack":1, 
                "no bump":1, 
                "no steal":0, 
                "no magic":0, 
                "no paralyze":0, 
                "no teleport":0]));
    SetItems(([]));
    SetExits( ([ 
                "south" : "/domains/town/room/thall",
                ]) );
    SetInventory(([
                "/domains/town/npc/clerk" : ({60, 1}),
                ]));
}
void init() {
    ::init();
    SetSmell(([]));
    SetListen(([]));
}
