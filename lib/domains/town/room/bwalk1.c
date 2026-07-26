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
    SetNightLong("这里是海滩上方的一片架高木制平台，人们可以在此散步欣赏风景，也可以光顾当地的商业设施。西边是哈里酒吧，北边是城镇码头。辽阔的大海向东方的地平线延伸。一盏孤灯照亮了这片区域。\n%^GREEN%^这里有一块你可以阅读的告示牌。%^RESET%^");
    SetDayLong("这里是海滩上方的一片架高木制平台，人们可以在此散步欣赏风景，也可以光顾当地的商业设施。西边是哈里酒吧，北边是城镇码头。辽阔的大海向东方的地平线延伸。\n%^GREEN%^这里有一块你可以阅读的告示牌。%^RESET%^");
    SetItems( ([
                "establishment":"西边的一家酒吧。",
                "local establishment":"西边的一家酒吧。",
                "commercial establishment":"西边的一家酒吧。",
                "sign":"地上的一块告示牌。输入 'read sign' 来阅读。",
                "platform":"脚下的地面。",
                "raised wooden platform":"脚下的地面。",
                "wooden platform":"脚下的地面。",
                "raised platform":"脚下的地面。",
                "horizon":"天空与大海相接之处。",
                "beautiful horizon":"天空与大海相接之处。",
                "town":"西北方的一处人口聚集地。",
                "boardwalk":"人们可以安稳行走并欣赏风景的地方。",
                "view":"东方美丽的地平线。",
                "dock":"北边船只停靠之处。",
                "shoreline":"陆地与海洋的分界线。",
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/docks",
                "west" : "/domains/town/room/hp.c",
                ]) );
    SetRead("sign", (: readSign :) );
    SetFrequency(5);
    SetChance(90);
    SetFish( ([
                "/domains/town/meals/shark" : 10,
                "/domains/town/meals/herring" : 2,
                ]) );
    SetActionsMap( ([ 
                "A soft breeze cools your brow." : 5,
                "You briefly hear seagulls far in the distance." : 7,
                "A cool breeze flows in from the east, " +
                "bringing with it the bracing salty smells of the sea.": 2,
                ]) );
    SetInventory( ([
                "/domains/town/obj/seawater" : 1,
                ]) );
    AddItem(new("/domains/town/obj/lamp"));
    SetSkyDomain("town");
}

void init(){
    ::init();
    add_action("enjoy","enjoy");
}

int enjoy(string foo){
    write("Mmmm!");
    return 1;
}
