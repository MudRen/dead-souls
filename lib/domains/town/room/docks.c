#include <lib.h>
#include <daemons.h>

inherit LIB_FISHING;

varargs string readSign() {
    string ret = "WARNING! Orcs, dwarves, and some other races cannot "+
        "swim! If you jump into the sea you will sink and drown!";
    return ret;
}

protected void create() {
    fishing::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("海湾码头");
    SetNightLong("这是一个由高架木制平台组成的区域，平台延伸到水中，方便有船的人们上下车。码头沿着海岸线向南延伸，变成了木板路。镇上的海岸在北边。大海一直延伸到东边的地平线。一根孤独的路灯照亮着这个区域。\n%^GREEN%^这里有一个标牌可以阅读。%^RESET%^");
    SetDayLong("这是一个由高架木制平台组成的区域，平台延伸到水中，方便有船的人们上下车。码头沿着海岸线向南延伸，变成了木板路。镇上的海岸在北边。大海一直延伸到东边的地平线。\n%^GREEN%^这里有一个标牌可以阅读。%^RESET%^");
    SetItems( ([
                "sign":"地上的一个标牌。要阅读它，请使用'read sign'命令。",
                "platform":"当地表面。"
                "raised wooden platform":"当地表面。"
                "wooden platform":"当地表面。"
                "raised platform":"当地表面。"
                "horizon":"天空与海相爱的地方。"
                "town":"西北方向的人口中心。"
                "boardwalk":"从这里向南延伸。"
                "dock":"船只在这里停靠的地方。"
                "shoreline":"陆地与海洋之间不连续的分界线。"
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
                "柔和的微风冷却着你的额头。" : 5,
                "你短暂地听到远处海鸥的叫声。" : 7,
                "一阵凉爽的微风从东边吹来，" +
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
