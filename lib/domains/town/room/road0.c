#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("萨奎弗路");
    SetNightLong("路灯照亮了这里的萨奎弗路，这条南北向的道路贯穿村庄。道路继续向北通往一些建筑，向南通往一个交叉口。");
    SetDayLong("这里是萨奎弗路，一条南北向的道路贯穿村庄。再向北一点看起来有一个酒馆和某种公会。向南是一个主要的交叉口。");
    SetItems( ([
                ({"pub","tavern","village pub"}) : "这是镇上传奇的酒馆，提供饮品并交换各种夸张的故事。",
                ({"guild","healers guild"}) : "这栋楼里是镇上唯一的医生的办公室。",
                "clouds" : "小小的蓬松云朵环绕着北部山峰。",
                ({"northern mountains","mountains","range","mountain range"}): 
                "雄伟的群山在遥远的北方，从这里看几乎是紫色的。",
                "intersection" : "主要的镇交叉口在南边。"
                ]) );
    SetSkyDomain("town");
    SetInventory(([
                "/domains/town/npc/beggar" : 1,
                ]));
    SetExits( ([
                "north" : "/domains/town/room/road",
                "south" : "/domains/town/room/start.c",
                ]) );

    AddTerrainType(T_ROAD);

    SetNoModify(0);
    AddItem(new("/domains/town/obj/lamp"));
}

void init(){
    ::init();
}
