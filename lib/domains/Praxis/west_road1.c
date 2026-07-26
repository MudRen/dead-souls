#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "西大道南端");
    SetLong(
            "西大道是贯穿普拉克西斯的主要住宅道路。道路两旁零星分布着"
            "一两栋房屋，直到南边在博克拉路到达尽头。路边排列的小屋"
            "相当破旧且不起眼。你可以听到里面传出的声音，居民们"
            "继续着他们的生活。");
    SetItems(
            (["road" : "西大道，标志着普拉克西斯的最西端。",
             "huts" : "它们是小小的农舍。",
             "hut" : "茅草屋顶，并不奢华。"
             ]) );
    SetSkyDomain("town");
    SetExits( 
            (["north" : "/domains/Praxis/west_road2",
             "south" : "/domains/Praxis/w_boc_la3"]) );
}
void init(){
    ::init();
}
