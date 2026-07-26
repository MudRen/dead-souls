#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "普拉克西斯西郊");
    SetLong(
            "普拉克西斯西边耸立着邪恶的达洛克山脉，"
            "保护着这片现实世界免受惩罚性的加吉普沙漠的侵袭。"
            "当地村庄的博克拉路向东通往镇中心。"
            "西大道从这里向北延伸。");
    SetExits(
            (["north" : "/domains/Praxis/west_road1",
             "west" : "/domains/Praxis/highway1",
             "east" : "/domains/Praxis/w_boc_la2"]) );
    SetItems(
            (["road" : "博克拉路贯穿普拉克西斯东西方向。",
             "roads" : "西大道和博克拉路。",
             "highway" : "通往噩梦世界西部土地的繁忙公路。当心达洛克山脉。",
             "mountains" : "达洛克山脉。据传有邪恶生物栖息其中。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
