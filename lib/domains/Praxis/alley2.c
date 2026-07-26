#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("no castle", 1);
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetSmell("default", "空气中弥漫着令人难以置信的恶臭。");
    SetSmell("dump", "闻起来像是各种恶心的腐烂物。");
    SetShort( "一条肮脏小巷的尽头");
    SetLong(
            "这是小巷的尽头。你周围可以看到腐朽的建筑。"
            "南边可以看到一座废弃的老建筑，因风吹日晒和缺乏维护而破败。"
            "北边有更多的废墟。这里似乎是普拉克西斯很久以前"
            "被废弃的另一整个区域。普拉克西斯垃圾场在更西边。");
    SetItems(
            (["alley" : "它穿过普拉克西斯最糟糕的区域。",
             "dump" : "人们把垃圾带到那里。总是在白天。",
             "building" : "看起来很久没有人关注过它了。",
             "ruins" : "涂鸦覆盖了它们。"]) );
    SetSkyDomain("town");
    SetExits( 
            ([ "east": "/domains/Praxis/alley1", 
             "north":"/domains/Praxis/wall",
             "south":"/domains/Praxis/building", 
             "west":"/domains/Praxis/dump" ]) );
}
void init(){
    ::init();
}
