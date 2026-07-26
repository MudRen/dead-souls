#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(40);
    SetShort("庄园外观");
    SetNightLong("你站在南边一座宏伟美丽的庄园外面，灯光照亮了庄园。它高耸于你之上，头顶可以看到二楼的一扇窗户开着。这里的草似乎有些杂乱，草坪向西延伸进入黑暗之中。庄园大门在北边。");
    SetDayLong("你站在南边一座宏伟美丽的庄园外面。它高耸于你之上，头顶可以看到二楼的一扇窗户开着。这里的草似乎有些杂乱，草坪向西延伸进入一片荒芜的花园。庄园大门在北边。");
    SetLong("你站在南边一座宏伟美丽的庄园外面。它高耸于你之上，头顶可以看到二楼的一扇窗户开着。这里的草似乎有些杂乱，草坪向西延伸进入一片荒芜的花园。庄园大门在北边。");
    SetItems( ([
                ({"house","mansion"}) : "一座庄严的华厦。",
                ({"window","second floor window"}) : "这是一扇高高在上的开着的窗户。如果你有梯子，也许能爬上去进入。",
                ({"grass","lawn","garden"}) : "相当杂乱的绿化。看起来园丁休假去了。",
                ({"gate","mansion gate"}) : "你现在所站庄园的入口。"
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
