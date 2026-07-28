#include <lib.h>
#include <daemons.h>

inherit LIB_FISHING;

varargs string readSign() {
    string ret = "警告！兽人、矮人和其他一些种族不会游泳！"+
        "如果你跳进海里，你会沉下去淹死的！";
    return ret;
}

protected void create() {
    fishing::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("海湾码头");
    SetNightLong("这里是一片架高的木制平台，延伸到水中，方便有船的人上下船只。码头沿着海岸线向南延伸，变成一条木栈道。城镇海岸在北边。辽阔的大海向东方的地平线延伸。一盏孤灯照亮了这片区域。\n%^GREEN%^这里有一块你可以阅读的告示牌。%^RESET%^");
    SetDayLong("这里是一片架高的木制平台，延伸到水中，方便有船的人上下船只。码头沿着海岸线向南延伸，变成一条木栈道。城镇海岸在北边。辽阔的大海向东方的地平线延伸。\n%^GREEN%^这里有一块你可以阅读的告示牌。%^RESET%^");
    SetItems( ([
                "sign":"地上的一块告示牌。输入 'read sign' 来阅读。",
                "platform":"脚下的地面。",
                "raised wooden platform":"脚下的地面。",
                "wooden platform":"脚下的地面。",
                "raised platform":"脚下的地面。",
                "horizon":"天空与大海相接之处。",
                "town":"西北方的一处人口聚集地。",
                "boardwalk":"从这里向南延伸。",
                "dock":"船只停靠之处。",
                "shoreline":"陆地与海洋的分界线。",
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/shore",
                "south" : "/domains/town/room/bwalk1.c",
                ]) );
    SetProperty("dock", 1);
    SetRead("sign", (: readSign :) );
    SetFrequency(5);
    SetChance(90);
    SetFish( ([
                "/domains/town/meals/shark" : 10,
                "/domains/town/meals/herring" : 20,
                ]) );
    SetActionsMap( ([ 
                "一阵微风拂过，带来凉爽。" : 5,
                "你短暂地听到了远处海鸥的叫声。" : 7,
                "一阵凉爽的微风从东方吹来，" +
                "带来了大海清新的咸味。": 2,
                ]) );
    SetInventory( ([
                "/domains/town/obj/seawater" : 1,
                ]) );
    AddItem(new("/domains/town/obj/lamp"));
    SetSkyDomain("town");
}

void init(){
    ::init();
}
