#include <lib.h>
#include <dirs.h>

inherit LIB_ROOM;

create() {
    ::create();
    SetProperties( (["no magic" : 1, "light" : 0, "no teleport" : 1]) );
    SetShort("蜘蛛坑");
    SetLong("你发现自己身处可怕的蜘蛛坑中。"
            "环绕你的地面和墙壁完全光滑，除了那些"
            "爬行的致命蜘蛛块。看起来，你最大的恐惧"
            "已经成真了：无处可逃。");
    SetItems( ([ "spiders" : "可怕的蜘蛛，死的活的都有，"
                "完全覆盖了坑的地面和墙壁。",
                ({ "wall", "walls", "floor" }) : "更多的蜘蛛。"]) );
}

void reset() {
    int x;
    ::reset();
    if(!present("spider", this_object())) 
        for(x=0; x<10; x++) {
            new("/domains/Praxis/obj/mon/spider")->move(this_object());
        }
}

void init() {
    ::init();
    if(this_player()->query_ghost()) { 
        this_player()->move(DIR_STANDARD_DOMAIN+"/square");
    }
}
