#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("萨奎沃路");
    SetNightLong("灯光照亮的萨奎沃路南北贯穿村庄。道路继续向北通往一些建筑，向南通往一个路口。");
    SetDayLong("这是萨奎沃路，南北贯穿村庄。北边稍远处看起来像是一家酒吧和某种公会。南边是一个主要路口。");
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
