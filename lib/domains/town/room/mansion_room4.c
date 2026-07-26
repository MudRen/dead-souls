#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("游戏室");
    SetLong("你在游戏室里。墙壁镶嵌着美丽的橡木板，厚厚的地毯踩在脚下感觉非常舒服。");
    SetItems( ([
                ({"wall","walls"}) : "漂亮的橡木镶板，涂着深沉而丰富的着色剂。",
                ({"carpet","carpeting"}) : "柔软、舒适，非常惬意。"
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
