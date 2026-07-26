#include <lib.h>
inherit LIB_ROOM;

int open;
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园主卧");
    SetLong("你在主卧室里。这里的装饰华丽、精美、奢华。显然住在这里的人既富有又有很高的品味。");
    SetItems( ([
                "decor" : "令人印象深刻，华丽而美丽。",
                ]) );
    SetInventory( ([
                "/domains/town/obj/bed" : 1,
                "/domains/town/obj/wardrobe" : 1,
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/mansion_uhall3"
                ]) );
    open = 0;

    SetDoor("north", "/domains/town/doors/m7.c");

}
int OpenPassage(){
    string desc;
    if(open == 1) return 1;
    tell_room(environment(this_player()),"A secret passageway is revealed!");
    open = 1;
    desc = GetLong();
    desc += "\n%^MAGENTA%^There is a newly-opened secret passageway here. %^RESET%^";
    SetLong(desc);
    AddItem(({"secret passageway","passageway"}) , "A passageway you can enter.");
    SetEnters(([ 
                "passageway" : "/domains/town/room/mansion_room11",
                "secret passageway" : "/domains/town/room/mansion_room11"
                ]) );
    return 1;
}
void init(){
    ::init();
}
