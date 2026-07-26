#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("村庄教堂");
    SetLong("几十年前，这座小小的单间教堂曾是村庄活动的中心。随着村庄的繁荣和世俗化，村民们越来越少来这里，直到它变得破败不堪、被人遗弃，正如你现在所见。这里到处都是害虫和蛛网，但没有遭到蓄意破坏，只是被灰尘所遗忘。西村路在南边，西墙上看起来像是一部电梯。\n%^GREEN%^电梯旁边有一个按钮。%^RESET%^");
    SetItems(([
                ({"elevator","elevator door","door"}) : "西墙上嵌入了一部看起来非常现代的电梯，在这座古朴的殖民时期教堂里显得格格不入。旁边有一个按钮，大概是用来呼叫电梯的。",
                "road" : "道路在南边。",
                ({"wall","west wall"}) : "西墙上嵌入了一部看起来非常现代的电梯，在这座古朴的殖民时期教堂里显得格格不入。旁边有一个按钮，大概是用来呼叫电梯的。",
                ({"church","place"}) : "一座老教堂。",
                ({"cobwebs","webs","web","vermin","dust","dirt"}) : "目前看不到害虫，但从蛛网和灰尘来看，显然有小型害虫在这里安了家。",
                "vandalism" : "你没有看到任何蓄意破坏的痕迹。"
                ]) );
    SetInventory(([
                "/domains/town/obj/charity" : 1,
                "/domains/town/obj/donation_box" : 1,
                ]));
    SetEnters( ([
                "elevator" : "/domains/town/room/elevator",
                ]) );
    AddItem(new("/domains/town/obj/church_button"));
    SetExits( ([
                "south" : "/domains/town/room/road1",
                "west" : "/domains/town/room/elevator",
                ]) );
}

void init(){
    ::init();
}
