#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetAmbientLight(25);
    SetShort( "山口");
    SetLong(
            "你在达洛克山脉最高点的西边。南边你可以看到一些"
            "不那么雄伟的山脉，被称为命运山脉。你正在行走的"
            "小径高高耸立在山脉之上，让你能够欣赏到噩梦世界"
            "的壮观景色。小路向东和向西延伸。" );
    SetItems(
            (["point" : "从这里看起来你能看到整个世界。",
             "pass" : "山口向下通往加吉普沙漠的荒凉之地。",
             "mountains" : "一条巨大的山脉，将东方肥沃的土地与沙漠分隔开来。",
             "valley" : "一个巨大的森林覆盖的山谷。",
             "desert" : "加吉普沙漠，许多旅行者在那里迷路且未被找到。",
             "mountain" : "它是较低的山峰之一，守护着山口。"]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "east" : "/domains/Praxis/pass2",
                ]) );
}
void reset() {
    ::reset();
    if(!present("balrog")) 
        new("/domains/Praxis/obj/mon/balrog")->move(this_object());
}
void init(){
    ::init();
}
