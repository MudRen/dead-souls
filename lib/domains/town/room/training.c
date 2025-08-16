#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("训练区域");
    SetLong("你在一个天花板很高、墙壁装有镜子、地板是硬木的大房间里。这个区域是为技能训练而设计的，虽然目前没有安排任何工作坊。冒险者公会的其余部分在楼下。");
    SetItems( ([
                ({"wall","walls"}) : "墙上装有镜子。",
                ({"mirror","mirrors"}) : "躲猫猫！",
                ({"hardwoord floor", "floor"}) : "地板是抛光木材制成的，"+
                "让人想起舞蹈学校里的那种地板。",
                ({"ceiling","high ceiling"}) : "高高的拱形天花板"+
                "提供了充足的空间。" 
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
