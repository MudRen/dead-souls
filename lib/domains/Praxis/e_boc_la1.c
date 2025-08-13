#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort("修道院南面的博克拉路东段");
    SetLong(
            "普瑞克斯东侧的博克拉路是一条大型土路，通往市中心纪念碑广场。许多 "
            "脚印已将道路踏成平坦的表面，便于行走。生锈的旧路灯柱矗立在道路两侧， "
            "在夜晚照亮普瑞克斯。一条向北的小径通向村庄修道院。博克拉路东段从这里继续向东延伸， "
            "而市政厅则在南面。");
    SetExits( 
            (["north" : "/domains/Praxis/monastery",
             "east" : "/domains/Praxis/e_boc_la2",
             "south" : "/domains/Praxis/town_hall.c",
             "west" : "/domains/Praxis/square"]) );
    SetItems(
            (["road" : "博克拉路是一条贯穿普瑞克斯的东西向大型道路。", 
             "monastery" : "梦魇世界的僧侣们在那里学习和 "
             "崇拜。", 
             "square" : "纪念碑广场是 "
             "整个普瑞克斯的中心点。许多冒险者喜欢在那里闲逛， "
             "与同僚们聊聊普瑞克斯的生活。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
