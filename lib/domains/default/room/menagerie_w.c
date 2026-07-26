#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("动物园西区");
    SetLong("这是动物园的西翼附属区域。");
    SetInventory(([
                "/domains/default/npc/dwarf" : 1,
                "/domains/default/npc/helf" : 1,
                "/domains/default/npc/artrell" : 1,
                "/domains/default/npc/halfling" : 1,
                "/domains/default/npc/nymph" : 1,
                "/domains/default/npc/avidryl" : 1,
                "/domains/default/npc/faerie" : 1,
                "/domains/default/npc/hobbit" : 1,
                "/domains/default/npc/pessis" : 1,
                "/domains/default/npc/kender" : 1,
                "/domains/default/npc/zoe" : 1,
                ]));
    SetExits(([
                "east" : "/domains/default/room/menagerie",
                ]));

}
void init(){
    ::init();
}
