#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "普拉克西斯商业区");
    SetLong("中心路向南通往繁忙的普拉克西斯港口，尽头是1号码头。"
            "商业生活在你周围匆忙进行，人们赶着在短暂的白昼结束前"
            "完成事务。在房地产交易所，高级凡人与强大的阿特摩斯"
            "进行房地产交易。在西北方的战士大厅里，战士们日夜"
            "聚集。普拉克西斯中心在东北方。");

    SetItems(
            ([({"path", "centre path"}) : "贯穿普拉克西斯南北的主要道路。",
             ({"pier", "port", "port of praxis"}) : "所有从海外进入"
             "普拉克西斯的货物都经过这里。",
             ({"hall", "hall of fighters"}) : "这个世界的战士们"
             "经常从各处聚集到这里。",
             "realty" : "高级凡人在这里购买建造城堡的材料。",
             "fighters" : "他们在战士大厅附近漫无目的地游荡。",
             "people" : "他们在这片区域忙着自己的事情。",
             "high mortals" : "最强大的凡人，通常是各职业的领袖。"])  );
    SetExits( ([
                "south" : "/domains/Praxis/pier1",
                "northwest" : "/domains/Praxis/fighter_join",
                "northeast" : "/domains/Praxis/s_centre3",
                ]) );
    SetListen("default", "你听到许多人忙碌的声音。");
    SetListen("fighters", "他们真的很吵闹且粗鲁。");
    SetSmell("money", "天哪，你真是太贪婪了。");
    SetSmell("fish", "你闻到南边码头上到处都是鱼腥味。");
}
void init(){
    ::init();
}
