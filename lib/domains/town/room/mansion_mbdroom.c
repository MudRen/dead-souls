#include <lib.h>
inherit LIB_ROOM;

int open;
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆主卧室");
你在主卧室里。这里的装饰美丽、华丽而奢华。很明显，住在这里的人很富有且品味高雅。 ";
    SetItems( ([
                "decor" : "令人印象深刻、华丽而美丽。",
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
    tell_room(environment(this_player()),"一个秘密通道被发现了！");
    open = 1;
    desc = GetLong();
    desc += "\n%^MAGENTA%^这里有一个新开放的秘密通道。 %^RESET%^";
    SetLong(desc);
    AddItem(({"secret passageway","passageway"}) , "你可以进入的通道。");
    SetEnters(([ 
                "passageway" : "/domains/town/room/mansion_room11",
                "secret passageway" : "/domains/town/room/mansion_room11"
                ]) );
    return 1;
}
void init(){
    ::init();
}
