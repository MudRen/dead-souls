#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("游戏室");
    SetLong("你在游戏室里。墙壁用美丽的橡木镶板装饰，"
            "厚厚的地毯踩在你脚下感觉非常舒服。");
    SetItems( ([
                ({"wall","walls"}) : "美丽的橡木镶板，"
                "有着深沉丰富的着色涂层。",
                ({"carpet","carpeting"}) : "它柔软、舒适且非常舒服。"
                ]) );
    AddStuff( ({
                "/domains/town/obj/btable",
                "/domains/town/obj/pool_table"
                }) );
    SetExits( ([
                "east" : "/domains/town/room/mansion_uhall2"
                ]) );

    SetDoor("east", "/domains/town/doors/m4.c");

}
void init(){
    ::init();
}
