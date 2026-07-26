#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("go_north", "north");
}

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("no castle", 1);
    SetShort( "达洛克山脉阴影下的西部公路");
    SetLong(
            "达洛克山脉在你西边高耸入云，遮蔽了天空，让大地上笼罩着"
            "一种诡异的暮色。南边有一条杂草丛生的小径，通往远处"
            "几座看起来相当不祥的山峰。"
            "提供东行路线的西部大公路在这里西边的一个山口处终止。"
            "北边环绕你的森林只有一个小小的缺口。");
    SetItems(
            (["peaks" : "你看到的山峰是命运山脉的双子峰。",
             "path" : "小径杂草丛生，似乎通往远处山峰的方向。",
             "mountains" : "一条巨大的山脉，将贫瘠的加吉普沙漠与东方的沃土分隔开来。",
             "mountain" : "卡泰希尔山，已知的哥布林据点。",
             "highway" : "西部大公路在这里的山口处终止。",
             ({"pass", "break"}) : "刚好够你通过。",
             "forest" : "一片非常黑暗、令人望而却步的森林。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["west" : "/domains/Praxis/pass1",
             "north" : "/domains/Praxis/orc_valley/guard",
             "east" : "/domains/Praxis/highway2"])  );
}

int go_north() {
    this_player()->eventMoveLiving("/domains/Praxis/orc_valley/guard", "north");
    return 1;
}
