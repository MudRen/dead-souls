#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "东大道附近的太阳巷");
    SetLong(
            "南边，这条阳光小巷的拐角处就是最后的龙餐厅。"
            "建筑是一座棕灰色的木质结构，外部几乎没有装饰。"
            "东大道在东边与这条小巷相交。森林的起始标志着"
            "普拉克西斯在这里的边界。");
    SetItems(
            (["foo" : "随便你怎么说。",
             "alley" : "这条小巷是普拉克西斯最北边的部分。"
             "只有北方大森林在更北边。",
             "restaurant" : "冒险之余休息的好地方。",
             "road" : "东大道。",
             "forest" : "普拉克西斯北边的巨大森林。"
             "有围墙的卡特西亚镇就在那边某处。",
             "border" : "森林阻止了普拉克西斯向北扩张。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["east" : "/domains/Praxis/east_road2",
             "west" : "/domains/Praxis/sun1",
             "south"	 : "/domains/Praxis/restaurant"]) );
}
void init(){
    ::init();
}
