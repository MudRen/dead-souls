#include <lib.h>

inherit LIB_FISHING;

void create() {
    ::create();
    SetProperty("no castle", 1);
    SetProperty("light", 3);
    SetProperty("night light", 2);
    SetMaxFishing(4);
    SetChance(10);
    SetShort( "普拉克西斯港口1号码头");
    SetLong(
            "欢迎来到普拉克西斯港口！\n"
            "1号码头几乎总是熙熙攘攘。来自整个世界的船只停靠在这里，"
            "为普拉克西斯及其周边地区运送货物。码头由坚固的木材建造，"
            "因雨水和咸湿的空气而变得风化。火炬排列在码头两侧，"
            "照亮了夜间的道路。沿着码头，你可以看到人们在钓鱼、"
            "聊天和享受天气。");
    SetSmell("default", "腐烂的鱼腥味刺激着你的鼻腔。");
    SetSmell("fish", "闻起来像是已经放了好几天了。");
    SetItems(
            (["port" : "来自噩梦世界各处的船只停靠在这里与普拉克西斯做生意。",
             "pier" : "港口的1号码头。",
             "goods" : "来自异域的商品。",
             "torch" : "它在夜间照亮码头。",
             "torches" : "它们在夜间照亮码头。"]) );
    SetExits( 
            (["north" : "/domains/Praxis/s_centre4" 	
             ]) );
}

void reset() {
    int i;

    ::reset();
    if(!present("stick"))
        new("/domains/Praxis/obj/misc/fishing_pole")->move(this_object());
    if(present("match")) return;
    i = 4;
    while(i--) new("/domains/Praxis/obj/misc/match")->move(this_object());
}
void init(){
    ::init();
}
