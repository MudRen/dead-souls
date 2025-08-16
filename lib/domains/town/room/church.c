#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("村庄教堂");
    SetLong("几十年前，这个小单间教堂是村庄活动的中心。随着村庄繁荣和世俗化，镇民们越来越少参加，直到它变得破败和被遗弃，就像你现在看到的那样。这个地方布满了害虫和蜘蛛网，但没有遭到破坏。只是积满灰尘的忽视。西村路在南边，西墙上看起来像是一部电梯。\n%^GREEN%^电梯旁边有一个按钮。%^RESET%^");
    SetItems(([
                ({"elevator","elevator door","door"}) : "嵌入西墙的是一部看起来非常现代化的电梯，在这个质朴的殖民式教堂里显得格格不入。旁边有一个按钮，大概是用来呼叫电梯的。",
                "road" : "路在南边。",
                ({"wall","west wall"}) : "嵌入西墙的是一部看起来非常现代化的电梯，在这个质朴的殖民式教堂里显得格格不入。旁边有一个按钮，大概是用来呼叫电梯的。"
                "road" : "路在南边。",
                ({"church","place"}) : "一座老教堂。"
                ({"cobwebs","webs","web","vermin","dust","dirt"}) : "目前看不到任何害虫，但从蜘蛛网和灰尘来看，很清楚小动物已经把这里当作了家。"
                "vandalism" : "你没有看到任何破坏行为。"
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
