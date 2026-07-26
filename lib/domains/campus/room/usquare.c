#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetAmbientLight(25);
    SetClimate("outdoors");
    SetShort("大学广场");
    SetLong("你在大学广场，一个鹅卵石铺就的十字路口，中间有一棵大树。东边是虚拟校区行政楼入口。这里有一个垃圾桶，保持区域整洁。北边有一条小路，似乎通往一个小镇。科学楼在南边。");
    SetItems(([
                ({"building","administrative building"}) : "这座大楼是虚拟校区工作人员的办公场所，大部分事务都在此办理。大楼内还设有快餐吧、小商店和学生休息室。",
                "clinic" : "这家小诊所是需要医疗护理的学生去的地方。"
                ]) );
    //SetSkyDomain("town");
    SetExits( ([
                "north" : "/domains/campus/room/npath",
                "east" : "/domains/campus/room/foyer",
                "south" : "/domains/campus/room/science1.c",
                ]) );
    SetProperties(([
                "no attack" : 0,
                ]));
    SetInventory(([
                "/domains/campus/npc/tim" : 1,
                "/domains/campus/npc/wim" : 1,
                "/domains/campus/chamber/tree" : 1,
                "/domains/campus/obj/bench" : 3,
                "/domains/campus/obj/trashcan" : 1,
                ]));
    SetEnters( ([ 
                ]) );
    AddItem(new("/domains/campus/obj/lamp"));
}

void init(){
    ::init();
}
