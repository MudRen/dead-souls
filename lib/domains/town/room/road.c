#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("萨奎沃路北段");
    SetNightLong("灯光照亮的萨奎沃路南北贯穿村庄。东边是村庄酒吧，这个传奇的饮酒之地曾接待过成千上万的盗贼、圣骑士以及介于两者之间的所有人。治疗师公会在西边。南边是一个主要路口。道路继续向北延伸进入黑暗之中。");
    SetDayLong("你在萨奎沃路上，这条路南北贯穿村庄。东边是村庄酒吧，这个传奇的饮酒之地曾接待过成千上万的盗贼、圣骑士以及介于两者之间的所有人。治疗师公会在西边，北边可以看到一条通往高原的路，边疆堡垒就坐落在那里。南边是一个主要路口。");
    SetItems( ([
                ({"pub","tavern","village pub"}) : "这是镇上传奇的饮酒之地，提供饮品，人们在这里交换夸大的故事。",
                ({"guild","healers guild"}) : "这栋建筑里是镇上唯一一位医生的诊所。",
                "clouds" : "蓬松的小云朵环绕着北方山脉的山峰。",
                ({"northern mountains","mountains","range","mountain range"}):
                "雄伟的山脉远在北方，从这里看几乎是紫色的。",
                "intersection" : "镇上主要的十字路口在南边。"
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
