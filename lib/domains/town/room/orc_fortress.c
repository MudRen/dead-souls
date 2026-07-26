#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(15);
    SetShort("兽人堡垒");
    SetLong("你发现自己身处当地兽人据点的入口。这个地方对正常人来说似乎相当不友好，建筑粗糙、不雅观，维护状况也很糟糕。这座木制堡垒看起来也有点业余，像是小孩子在玩打仗游戏拼凑起来的。南边有一个通往外面的出口，西边可以看到另一个房间。");
    SetExits( ([
                "south" : "/domains/town/room/valley",
                "west" : "/domains/town/room/orc_temple.c",
                ]) );
    SetSmell( ([ "default" : "The stench of garbage and animal waste hangs here."]) );
    SetInventory(([
                "/domains/town/npc/orc" : 1,
                "/domains/town/npc/orc2" : 1,
                "/domains/town/npc/orc_boss" : 1,
                ]));
}
void init(){
    ::init();
}
