#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(15);
    SetShort("兽人堡垒");
    SetLong("你深入兽人据点的腹地。就像你见过的堡垒其他部分一样，这里看起来是匆忙搭建的，建造得相当笨拙，而且维护很差。这里是某种仪式室或神殿。干涸的血迹环绕着一个高起的祭坛，各种头骨装饰着墙壁。堡垒的其他部分在东边。");
    SetItems(([
                ({ "skull","skulls" }) : "你看到一些你能认出种族的头骨，但大多数你认不出来。这里至少有一个人类头骨。有些头骨非常新鲜，还是湿的，上面还挂着组织。",
                ({"chamber","ceremonial chamber","temple"}) : "一个进行兽人仪式的地方。",
                ({"blood","dried blood"}) : "显然祭坛周围的地面收集了祭坛上发生的事件所产生的血迹。",
                ({"wall","walls"}) : "粗糙的土木墙壁。",
                ]) );
    SetExits( ([ 
                "east" : "/domains/town/room/orc_fortress",
                ]) );
    SetSmell( ([ "default" : "The stench of garbage and animal waste hangs here."]) );
    SetInventory(([
                "/domains/town/obj/altar" : 1,
                "/domains/town/npc/orc_shaman" : 1,
                ]));

}
void init(){
    ::init();
}
