#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "克拉斯纳广场北面的中心大道");
    SetLong("中心大道是一条人来人往的土路，南北贯穿普瑞克斯。就在南边不远处，它与博克拉路在克拉斯纳广场相交。西侧是一座小教堂。这是一座中等大小的建筑，由坚固的木头建成，漆成白色。一扇非常简单但美丽的彩色玻璃窗从教堂正面凝视着你。门是深黑色的，其中一扇微微敞开，表示欢迎。东侧是当地的旅店。");
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetItems(
            (["path" : "中心大道向南通往纪念碑广场，向北通往城外。",
             "road" : "博克拉路是主要的东-西向道路。",
             "church" : "这是一座由当地牧师管理的小教堂。",
             "square" : "普瑞克斯的中心广场。"]) );
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
