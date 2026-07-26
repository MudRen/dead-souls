#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("宽阔的小路");
    SetLong("这是一条南北走向的铺砌小路。两侧是茂密的灌木丛。小镇在北边。南边似乎是一个大学校园。");
    SetItems( ([
                ({ "bush","bushes","side","sides"}) : "高大茂密的灌木丛挤满了小路两侧。",
                "path" : "一条宽阔的鹅卵石小路，南北走向。",
                ({ "sign","post","signpost"}) : "一根柱子插在地上，上面挂着一块告示牌。",
                "town" : "从这里你无法看清太多。",
                "campus" : "从这里你无法看清太多。"
                ]) );
    //SetSkyDomain("town");
    SetInventory(([
                ]));
    SetRead( "sign", "小心！你正在离开虚拟校区的安全区域。");
    SetExits( ([ "south" : "/domains/campus/room/npath",
                "north" : "/domains/campus/room/south_road2",
                ]) );
    AddItem(new("/domains/campus/obj/lamp"));
}
void init(){
    ::init();
}
