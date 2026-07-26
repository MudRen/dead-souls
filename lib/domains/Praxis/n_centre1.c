#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "克拉斯纳广场北侧的中心路");
    SetLong("中心路是一条贯穿普拉克西斯南北的繁忙土路。就在南边，"
            "它在克拉斯纳广场与博克拉路交汇。西边有一座小教堂。"
            "这是一座中等大小的建筑，由坚固的木材制成，刷成了白色。"
            "教堂正面有一扇简洁而美丽的彩色玻璃窗。门是深黑色的，"
            "其中一扇微微敞开，表示欢迎。东边是当地的旅馆。");
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetItems(
            (["path" : "中心路向南通往纪念碑广场，向北出城。",
             "road" : "博克拉路是主要的东西向道路。",
             "church" : "一座由当地牧师管理的小教堂。",
             "square" : "普拉克西斯的中央广场。"]) );
    SetSkyDomain("town");
    SetExits( ([
                "south" : "/domains/Praxis/square",
                "west" : "/domains/Praxis/cleric_join",
                "north" : "/domains/Praxis/n_centre2",
                "east" : "/domains/Praxis/hotel.c",
                ]) );
}
void init(){
    ::init();
}
