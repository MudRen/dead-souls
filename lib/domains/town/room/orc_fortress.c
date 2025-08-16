#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(15);
    SetShort("兽人要塞");
    SetLong("你发现自己身处当地兽人据点的入口。这个地方对正常人的感受来说似乎相当不友好，因为建筑粗糙、不雅，维护也很肮脏。这座木制堡垒看起来也有些业余地拼凑在一起，就好像是年轻人在假扮士兵。南边有一个出口通往外面，西边可以看到另一个房间。");
    SetExits( ([
                "south" : "/domains/town/room/valley",
                "west" : "/domains/town/room/orc_temple.c",
                ]) );
    SetSmell( ([ "default" : "垃圾和动物粪便的恶臭弥漫在这里。"]) );
    SetInventory(([
                "/domains/town/npc/orc" : 1,
                "/domains/town/npc/orc2" : 1,
                "/domains/town/npc/orc_boss" : 1,
                ]));
}
void init(){
    ::init();
}
