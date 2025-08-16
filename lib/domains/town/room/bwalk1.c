#include <lib.h>
#include <daemons.h>

inherit LIB_FISHING;

varargs string readSign() {
    string ret = "警告！兽人、矮人和一些其他种族不会游泳！如果你跳进海里会下沉并淹死！";
    return ret;
}

protected void create() {
    fishing::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("海湾码头");
    SetNightLong("这是一个由海滩上方的高架木制平台组成的区域，让人们可以四处走动欣赏风景，也许还可以参观当地的商业场所。西边是哈里酒吧，北边是镇上的码头。大海向东方地平线延伸。一盏孤独的路灯照亮这个区域。\n%^GREEN%^这里有一个你可以阅读的标牌。%^RESET%^");
    SetDayLong("这是一个由海滩上方的高架木制平台组成的区域，让人们可以四处走动欣赏风景，也许还可以参观当地的商业场所。西边是哈里酒吧，北边是镇上的码头。大海向东方地平线延伸。\n%^GREEN%^这里有一个你可以阅读的标牌。%^RESET%^");
    SetItems( ([
                "establishment":"西边的一家酒吧.",
                "local establishment":"西边的一家酒吧."
                "commercial establishment":"西边的一家酒吧."
                "sign":"地上的一个标牌。要阅读它，请使用'read sign'命令."
                "platform":"The local surface.",
                "raised wooden platform":"The local surface.",
                "wooden platform":"The local surface.",
                "raised platform":"The local surface.",
                "horizon":"Where the sky loves the sea.",
                "beautiful horizon":"Where the sky loves the sea.",
                "town":"西北方向的人口中心."
                "boardwalk":"人们可以稳定行走并欣赏风景的地方."
                "view":"东方美丽的地平线."
                "dock":"北边船只停靠的地方."
                "shoreline":"陆地与海洋不连续性之间的分界线."
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
                "柔和的微风拂过你的额头。" : 5,
                "你短暂地听到远处海鸥的声音。" : 7,
                "一阵凉爽的微风从东方吹来，带来了令人振奋的海洋咸咸的气味。": 2,
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
    write("嗯！");
    return 1;
}
