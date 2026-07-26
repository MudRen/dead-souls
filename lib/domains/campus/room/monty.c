#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("概率实验室一");
    SetLong("这是一间干净、无菌的实验室，墙壁洁白发亮。北墙上有三扇门：一扇%^RED%^红色%^RESET%^的，一扇%^GREEN%^绿色%^RESET%^的，一扇%^BLUE%^蓝色%^RESET%^的。\n%^GREEN%^墙上有一块大告示牌，你可以阅读。%^RESET%^");
    SetInventory( ([
                "/domains/campus/obj/pedestal" : 1,
                "/domains/campus/npc/charly" : 1
                ]) );
    SetItems( ([
                ({ "wall","walls","north wall"}) : "闪亮的白色实验室墙壁。",
                "red room" : "这里没有红房间。",
                "green room" : "这里没有绿房间。",
                "blue room" : "这里没有蓝房间。",
                ]) );
    SetObviousExits("north");
    SetExits( ([ 
                "north" : "/domains/campus/room/wiz_lab",
                ]) );
    AddItem( ({"sign","sign on the wall"}), "A sign you can read.",({"large"}) );

    SetEnters( ([
                "red room" : "/domains/campus/room/red_room",
                "green room" : "/domains/campus/room/green_room",
                "blue room" : "/domains/campus/room/blue_room"
                ]) );
    SetDoor("red room","/domains/campus/doors/red_door");
    SetDoor("green room","/domains/campus/doors/green_door");
    SetDoor("blue room","/domains/campus/doors/blue_door");
    SetNoClean(1);
}
void init(){
    ::init();
    SetRead(({"sign","sign on the wall"}), "Press the button on "
            "the pedestal to reset the experiment.", "Common");
}
