#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("climb", "climb");
}

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "东大道南端");
    SetLong(
            "踏上东大道的旅程，你可以看到这是一条不太繁忙的街道。"
            "博克拉路在南边，笔直穿过普拉克西斯。偶尔可以看到"
            "一两盏路灯，已经古老生锈。杂货店的围墙紧邻道路"
            "西侧，而普拉克西斯图书馆，这个领域最大的图书馆之一，"
            "在东边。");
    SetItems(
            (["road" : "东大道，标志着普拉克西斯的最东端。",
             "roads" : "东大道和博克拉路。",
             "side" : "那是杂货店。",
             "shop" : "当地冒险者杂货店坐落在博克拉路和东大道的交汇处。",
             "walls" : "没什么特别的。",
             "wall" : "你相当确定自己爬不上去。",
             "library" : "开放供你阅读。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["north" : "/domains/Praxis/east_road2",
             "south" : "/domains/Praxis/e_boc_la3",
             "east"	 : "/domains/Praxis/library"]) );
    SetProperty("no castle", 1);
}

int climb(string str) {
    if(!str) {
        notify_fail("爬什么？\n");
        return 0;
    }
    if(str != "wall" && str != "walls") {
        notify_fail("这里没有可以攀爬的东西。\n");
        return 0;
    }
    if(this_player()->query_stats("dexterity") < random(30)) {
        write("哎呀！你在攀爬时滑倒受伤了！");
        say(this_player()->query_cap_name()+"在攀爬围墙时滑倒受伤了。");
        this_player()->add_hp(-(random(7)));
    }
    else {
        write("你没法成功攀爬上去。");
        say(this_player()->query_cap_name()+"试图攀爬商店围墙但失败了。");
    }
    return 1;
}
