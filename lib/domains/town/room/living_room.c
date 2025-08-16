#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("客厅");
    SetLong("这是老房子的客厅。这是一个小而朴素的住宅，显然是为了实用性而非华丽而建造的。北边的门廊通向前面。");
    SetItems(([
                ({ "forest", "wood", "vegetation" }) : "周围都是长得极其茂密的植被，根本不可能偏离小径。",
                ({ "porch", "front porch" }) : "一栋白色老房子的木制前廊。",
                ({ "trail", "path" }) : "向北，一条狭窄的小径通向树林。",
                ({ "clearing", "woods" }) : "仿佛被强大的魔法清空，树林在这里让出空地，房子就矗立在这里。",
                ({ "house", "white house", "old house" }) : "房子看起来很破旧，维护不善，相当老旧。它的建造采用了不再使用的古老设计。尽管外观饱受摧残，房子似乎仍保持着一种安静的尊严，仿佛多年来有许多人曾是它的朋友，而它只是在等待他们的归来。",
                ]));
    SetInventory(([
                "/domains/town/obj/sofa" : 1,
                "/domains/town/obj/simple_chair" : 2,
                ]));
    SetExits(([
                "north" : "/domains/town/room/porch",
                ]));

    SetDoor("north", "/domains/town/doors/house_door.c");

}
void init(){
    ::init();
}
int CanReceive(object ob){
    if(answers_to("provost",ob)) return 0;
    return ::CanReceive();
}
