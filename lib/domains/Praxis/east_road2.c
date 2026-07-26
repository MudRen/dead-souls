#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetListen( "default", "空气中回荡着蟋蟀轻柔的鸣叫声。");
    SetShort( "东大道与太阳巷交叉口");
    SetLong(
            "太阳巷因其美丽的日落景色而得名，从东大道向西延伸。"
            "东大道继续沿城镇东部边界南北延伸。向东，你可以看到"
            "普拉克西斯墓地，被大树遮蔽。这里的空气非常静谧，"
            "一种不祥的预感弥漫在空气中。");
    SetItems(
            (["alley" : "一条明亮而欢快的小巷，标志着普拉克西斯的北部边界。",
             "road" : "东大道是一条在普拉克西斯东部蜿蜒南北的道路。",
             "cemetery" : "普拉克西斯的居民安葬在那里。看起来阴森恐怖。",
             "trees" : "树木是高大的垂柳。",
             "forest" : "一片标志着普拉克西斯北端的大森林。"])
            );
    SetSkyDomain("town");
    SetExits( 
            (["north" : "/domains/Praxis/east_road3",
             "south" : "/domains/Praxis/east_road1",
             "east" : "/domains/Praxis/cemetery/grave_yard",
             "west"	 : "/domains/Praxis/sun2"]) );
}

void init(){
    ::init();
}
