#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("房子北边");
    SetLong("茂密的树林在这里让位于一片小空地，一座漆成白色的旧房子矗立其中。房子的前廊在南边，一条狭窄的小径向北通往树林深处。");
    SetItems(([
                ({ "forest", "wood", "vegetation" }) : "四周的植被生长得异常茂密，让人无法偏离小路。",
                ({ "porch", "front porch" }) : "一座白色旧房子的木质前廊。",
                ({ "trail", "path" }) : "北边有一条狭窄的小路通向树林。",
                ({ "clearing", "woods" }) : "仿佛有某种强大的魔法，树林在这里变得开阔，房子就矗立于此。",
                ({ "house", "white house", "old house" }) : "这座房子看起来饱经风霜、年久失修，相当老旧。它的建筑风格已经过时。尽管外表破旧，这座房子似乎有一种静谧的尊严，仿佛多年来许多人曾是它的朋友，而它只是在等待他们的归来。",
                ]));
    SetSkyDomain("town");
    SetExits( ([
                "north" : "/domains/town/room/narrow_path2",
                "south" : "/domains/town/room/porch.c",
                ]) );
    SetInventory(([
                "/domains/town/obj/mailbox" : 1,
                ]));

}
void init(){
    ::init();
}

int CanReceive(object ob){
    if(answers_to("provost",ob)) return 0;
    return ::CanReceive();
}
