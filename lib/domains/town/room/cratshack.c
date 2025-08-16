#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("房子北面");
    SetLong("茂密的树林在这里让出一个小空地，一栋刷成白色的老房子矗立在这里。房子的前廊在南边。一条狭窄的小径向北通向树林深处。");
    SetItems(([
                ({ "forest", "wood", "vegetation" }) : "周围都是长得极其茂密的植被，根本不可能偏离小径。",
                ({ "porch", "front porch" }) : "一栋白色老房子的木制前廊。",
                ({ "trail", "path" }) : "向北，一条狭窄的小径通向树林。",
                ({ "clearing", "woods" }) : "仿佛被强大的魔法清空，树林在这里让出空地，房子就矗立在这里。",
                ({ "house", "white house", "old house" }) : "房子看起来很破旧，维护不善，相当老旧。它的建造采用了不再使用的古老设计。尽管外观饱受摧残，房子似乎仍保持着一种安静的尊严，仿佛多年来有许多人曾是它的朋友，而它只是在等待他们的归来。",
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
