#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("训练区");
    SetLong("你在一个天花板很高、墙壁装有镜子、地板为硬木的大房间里。这个区域是为技能训练设计的，不过目前没有安排任何研讨会。冒险者公会的其他部分在楼下。");
    SetItems( ([
                ({"wall","walls"}) : "墙壁上镶嵌着镜子。",
                ({"mirror","mirrors"}) : "躲猫猫！",
                ({"hardwoord floor", "floor"}) : "地板由抛光木材制成，让人联想到舞蹈学校的地板。",
                ({"ceiling","high ceiling"}) : "高高的拱形天花板提供了充足的空间。"
                ]) );
    SetExits( ([ 
                "down" : "/domains/town/room/adv_guild",
                ]) );
    SetInventory(([
                "/domains/town/npc/radagast" : ({60, 1}),
                "/domains/town/obj/bbucket" : 1,
                ]));
    SetPlayerKill(1);
}
void init(){
    ::init();
}
