#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(40);
    SetShort("公馆外部");
    SetLong("你站在一座大型美丽公馆的外面，公馆位于你南边。它高耸于你之上，头顶上你可以看到二楼的一个窗户是开着的。这里的草看起来有些野性，草坪向西延伸到一个杂草丛生的花园。公馆大门在北边。");
    SetItems( ([
                ({"house","mansion"}) : "一座庄严的欢乐宫殿。",
                ({"window","second floor window"}) : "这是一个开着的窗户，在你头顶很高处。如果你有梯子，你可能能够爬上去进入。",
                ({"grass","lawn","garden"}) : "相当杂乱的绿植。看起来园丁一直在度假。",
                ({"gate","mansion gate"}) : "你现在所站立的庄园的入口点。"
                ]) );
    SetSkyDomain("town");
    SetExits( ([
                "north" : "/domains/town/room/gate",
                "west" : "/domains/town/room/garden",
                "south" : "/domains/town/room/mansion_int",
                ]) );
    SetDoor("south","/domains/town/doors/mansion");
    AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    ::init();
}
