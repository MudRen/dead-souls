/*    /domains/Ylsrim/room/kaliid4.c
 *    From the Dead Souls Mud Library
 *    A simple example room
 *    Created by Descartes of Borg 950929
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("卡利德路集市北侧");
    SetLong("卡利德路向东西方向延伸，横跨伊尔斯利姆，一望无际。"
            "南边，卡利德路通向中心集市，商贩们日夜在那里出售商品。"
            "路对面是当地冒险者大厅的入口。");
    SetSkyDomain("town");
    SetExits( ([ 
                "east" : "/domains/Ylsrim/room/kaliid3",
                "south" : "/domains/Ylsrim/room/bazaar",
                "west" : "/domains/Ylsrim/room/kaliid5",
                "north" : "/domains/Ylsrim/room/adv_hall",
                ]) );
    AddItem("hall", "一座小型建筑，是伊尔斯利姆著名的冒险活动的核心场所。", ({ "adventurer", "adventurers" }));
    AddItem("bazaar",  "中心集市是伊尔斯利姆的主要市场。虽然许多店铺夜间关门，"
            "但商贩们全天都在集市上游荡兜售商品。",
            ({ "central" }));
    AddItem("vendor", "集市上有许多商贩在四处游荡。");
    AddItem("town", "一个新城镇，在这里北边。");
    AddItem("road", "伊尔斯利姆的主要街道。", ({ "kaliid" }));
}

void init(){
    ::init();
}
