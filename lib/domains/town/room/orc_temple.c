#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(15);
    SetShort("兽人要塞");
    SetLong("你在兽人要塞深处。就像你看到的堡垒其他部分一样，这里看起来匆忙拼凑而成，而且建造得很笨拙，维护也很差。这是某种仪式室或神庙。干涸的血液围绕着一座升高的祭坛，各种类型的头骨装饰着墙壁。堡垒的其他部分在东边。");
    SetItems(([
                ({ "skull","skulls" }) : "你看到有些头骨你能认出种族，但大多数你认不出来。这里至少有一个人的头骨。有些还很新鲜，仍然是湿的，上面还挂着组织。",
                ({"chamber","ceremonial chamber","temple"}) : "进行兽人仪式的地方。",
                ({"blood","dried blood"}) : "显然祭坛周围的地面收集了祭坛上发生事情时的血液。",
                ({"wall","walls"}) : "粗糙的土墙和木墙。"
                ]) );
    SetExits( ([ 
                "east" : "/domains/town/room/orc_fortress",
                ]) );
    SetSmell( ([ "default" : "垃圾和动物粪便的恶臭弥漫在这里。"]) );
    SetInventory(([
                "/domains/town/obj/altar" : 1,
                "/domains/town/npc/orc_shaman" : 1,
                ]));

}
void init(){
    ::init();
}
