#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("前廊");
    SetLong("这是一座老房子摇摇欲坠的前廊。前门在南边。北边是树林中的一片空地，还有一条小路延伸出去。");
    SetItems(([
                ({ "forest", "wood", "vegetation" }) : "周围都是生长得极其茂密的植被，不可能离开小径闲逛。",
                ({ "porch", "front porch" }) : "一座古老白色房子的木制前廊。",
                ({ "trail", "path" }) : "北边有一条狭窄的小路通向树林。",
                ({ "clearing", "woods" }) : "仿佛被强大的魔法所作用，树林在这里清出了一片空地，房子就坐落在这里。",
                ({ "house", "white house", "old house" }) : "这座房子看起来饱经风霜，维护不善，相当古老。它的建造采用了不再使用的古老设计。尽管外观残破，这座房子似乎有一种安静的尊严，仿佛多年来许多人曾是它的朋友，它只是简单地等待着他们的归来。"
                ]));
    SetInventory(([
                "/domains/town/obj/rocking_chair" : 2,
                ]));
    SetExits( ([
                "north" : "/domains/town/room/cratshack",
                "south" : "/domains/town/room/living_room.c",
                ]) );

    SetDoor("south", "/domains/town/doors/house_door.c");

}
void init(){
    ::init();
}
int CanReceive(object ob){
    if(answers_to("provost",ob)) return 0;
    return ::CanReceive();
}
