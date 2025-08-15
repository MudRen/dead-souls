#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("萨奎弗路北段");
    SetNightLong("路灯照亮了萨奎弗路，这条南北向的道路贯穿村庄。东边是村里的酒馆，这个传奇的聚会场所曾被无数盗贼、圣骑士以及介于两者之间的所有人使用。西边是医疗师公会。南边是一个主要交叉口。道路向北延伸进入黑暗中。");
    SetDayLong("你在萨奎弗路上，这条南北向的道路贯穿村庄。东边是村里的酒馆，这个传奇的聚会场所曾被无数盗贼、圣骑士以及介于两者之间的所有人使用。西边是医疗师公会，向北你可以看到一条通往高原的道路，那里矗立着边境要塞。南边是一个主要交叉口。");
    SetItems( ([
                ({"pub","tavern","village pub"}) : "这是镇上传奇的聚会场所，提供饮品并交换各种夸张的故事。",
                ({"guild","healers guild"}) : "这栋楼里是镇上唯一的医生的办公室。",
                "clouds" : "小小的蓬松云朵环绕着北部山峰。",
                ({"northern mountains","mountains","range","mountain range"}): 
                "雄伟的群山在遥远的北方，从这里看几乎是紫色的。",
                "intersection" : "主要的镇交叉口在南边。"
                ]) );
    SetSkyDomain("town");
    SetInventory(([
                "/domains/town/weap/knife" : 1,
                ]));
    SetExits( ([
                "north" : "/domains/town/room/mountain_road",
                "east" : "/domains/town/room/tavern",
                "west" : "/domains/town/room/healer",
                "south" : "/domains/town/room/road0.c",
                ]) );
    AddTerrainType(T_ROAD);

    SetEnters( ([
                "pub" : "/domains/town/room/tavern",
                "guild" : "/domains/town/room/healer",
                "healers guild" : "/domains/town/room/healer"
                ]) );
    SetNoModify(0);
    AddItem(new("/domains/town/obj/lamp"));
}

void init(){
    ::init();
}
