#include <lib.h>
inherit LIB_CHAPEL;

protected void create() {
    chapel::create();
    SetTown("town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("镇公所办事员");
    SetLong("这个小办公室是人们来办理官方公共事务的地方。镇公所的主要区域在南边。");
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
