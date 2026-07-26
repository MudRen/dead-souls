#include <lib.h>
#include <message_class.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("LPC大学接待处");
    SetLong("你身处虚拟校区招生办公室狭小而简朴的接待区。一扇门通往北面的行政楼主走廊。");
    SetExits( ([
                "north" : "/domains/campus/room/corridor",
                ]) );
    SetNoModify(1);
    SetDoor("north","/domains/campus/doors/plain_door");
    SetInventory(([
                "/domains/campus/obj/bbucket" :1,
                "/domains/campus/npc/jennybot" : ({60, 1}),
                ]));
    SetProperty("no attack", 1);
    SetCoordinates("4000,4000,0");
}

void init(){
    ::init();
}

mixed CanReceive(object ob){
    if(ob && ob->GetRace() == "rodent"){
        message("info","You are repelled by rodenticide.",ob);
        return 0;
    }
    return ::CanReceive(ob);
}
