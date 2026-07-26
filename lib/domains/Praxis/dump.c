#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetSmell("default", "你差点被这里的恶臭熏晕过去。");
    SetSmell("piles", "闻起来像是腐烂的精灵食物。");
    SetSmell("food", (: this_object(), "smell_food" :));
    SetProperty("light", 3);
    SetShort( "普拉克西斯垃圾场");
    SetLong(
            "整个城镇的废物都堆积在普拉克西斯垃圾场。"
            "你周围是一堆又一堆的垃圾和其他散发恶臭的"
            "无法辨认的东西。一条小巷向东延伸。");
    SetItems(
            (["mounds" : "谁知道那堆垃圾里会有什么？",
             "dump" : "普拉克西斯的人们把垃圾带到这里。",
             "trash" : "什么东西都有。",
             "alley" : "通往中心路。"]) );
    SetExits( 
            (["east" : "/domains/Praxis/alley2"]) );
}

void reset() {
    ::reset();
    SetSearch("mound", (: this_object(), "mound_searching" :));
    SetSearch("mounds", (: this_object(), "mound_searching" :));
}

void mound_searching() {
    message("my_action", "你在一堆垃圾中找到了一把匕首！", this_player());
    message("other_action", this_player()->query_cap_name()+
            "在一堆垃圾中找到了一把匕首。", this_object(),
            ({ this_player() }));
    new("/domains/Praxis/obj/weapon/dagger")->move(this_object());
    RemoveSearch("mounds");
    RemoveSearch("mound");
}

void smell_food(string str) {
    message("my_action", "你被腐烂精灵食物的恶臭熏晕过去了。", this_player());
    message("other_action", this_player()->query_cap_name()+
            "被腐烂精灵食物的恶臭熏晕过去了。", this_object(),
            ({ this_player() }));
    this_player()->add_sp(-3);
    this_player()->add_hp(-3);
    this_player()->set_paralyzed(10, "你恶心到无法动弹！");
}
void init(){
    ::init();
}
