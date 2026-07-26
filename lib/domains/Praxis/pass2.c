#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetAmbientLight(25);
    SetShort( "山口");
    SetLong(
            "你处于穿越达洛克山脉的黑暗山口的最高点。"
            "向下望去，你可以看到西边贫瘠的加吉普沙漠。"
            "据传进入沙漠的人很少能活着出来。"
            "远处东方你可以看到森林山谷的柔和起伏。"
            "正前方，一个小洞穴通向山中。");
    SetItems(
            (["point" : "从这里看起来你能看到整个世界。",
             "pass" : "它从西蜿蜒到东南。",
             "mountains" : "一条巨大的山脉，将东方肥沃的土地与沙漠分隔开来。",
             "valley" : "一个巨大的森林覆盖的山谷。",
             "desert" : "加吉普沙漠，许多旅行者在那里迷路且未被找到。",
             "forest" : "山附近黑暗而阴沉，但东边看起来更友好。",
             "cave" : "洞穴在你面前显得非常黑暗和不祥。",
             "mountain" : "它是较低的山峰之一，守护着山口。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["west" : "/domains/Praxis/pass3",
             "southeast" : "/domains/Praxis/pass1",
             "north"	 : "/domains/Praxis/mountains/entrance"]) );
}
void init(){
    ::init();
}
