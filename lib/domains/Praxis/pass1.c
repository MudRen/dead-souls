#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( (["light":3, "no castle" : 1 ]) );
    SetShort( "达洛克山脉山口东端");
    SetLong( "沿着这条巨大的峡谷向下望去，你可以看到"
            "西部大公路蜿蜒向东延伸。向左转弯，这条小路通往"
            "达洛克山脉，据传那里生活着哥布林、炎魔和塔克达洛克。"
            "这片区域非常崎岖和危险，文明已经被你远远抛在身后。"
            "西边不远处就是小路的最高点。");
    SetItems( (["pass" : "穿过达洛克山脉的阴暗山口。",
                "highway" : "西部大公路。它通往普拉克西斯。",
                "lands" : "东方肥沃的土地。",
                "range" : "达洛克山脉，许多邪恶生物的家园。",
                "mountains" : "达洛克山脉，许多邪恶生物的家园。",
                "territory" : "它属于地下的邪恶生物。",
                "point" : "从那里，山口向西下行通往加吉普沙漠。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["northwest" : "/domains/Praxis/pass2",
             "east" : "/domains/Praxis/highway3"]) );
}
void init(){
    ::init();
}
