#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("宽阔的小路");
    SetLong("这是一条从大学广场向北延伸的铺砌小路。两侧是茂密的灌木丛。虚拟校区在南边。北边你看到的似乎是一个小镇。");
    SetItems( ([
                ({ "bush","bushes","side","sides"}) : "高大茂密的灌木丛挤满了小路两侧。",
                "path" : "一条宽阔的鹅卵石小路，南北走向。",
                "town" : "从这里你无法看清太多。"
                ]) );
    //SetSkyDomain("town");

    SetExits( ([ "south" : "/domains/campus/room/usquare",
                "north" : "/domains/campus/room/npath2",
                ]) );
    AddItem(new("/domains/campus/obj/lamp"));
}
void init(){
    ::init();
}
