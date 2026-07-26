#include <lib.h>
inherit LIB_ROOM;

int revealed;

protected void create(){
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("起居室");
    SetLong("你在一间豪华的起居室里，装饰和家具与庄园的其他地方一样，品味卓越，注重细节。");
    SetItems( ([
                ({"furniture","furnishings","decorations"}) :
                "你看到了精致审美品味的体现。"
                ]) );
    SetExits( ([
                "west" : "/domains/town/room/mansion_int.c",
                ]) );
    SetInventory( ([
                "/domains/town/obj/rug" :1,
                "/domains/town/npc/thief" :1
                ]) );
    revealed = 0;
}
int TellRevealed(){
    if(revealed) return revealed;
    else return 0;
}
int RevealDoor(){
    if(revealed == 1) {
        tell_room(this_object(),"The trapdoor is already visible.");	
        return 1;
    }
    revealed = 1;

    tell_room(this_object(),"A trapdoor is revealed!");
    AddExit("down","/domains/town/room/mansion_room12");
    SetDoor("down","/domains/town/doors/trapdoor");
    return 1;
}
void init(){
    ::init();
}
