#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("大舞厅");
    SetLong("这个巨大的房间在规模和"
            "装饰上都令人惊叹。显然是公馆的中心，"
            "这个舞厅可以轻松容纳数百名"
            "客人。拱形天花板高达数十英尺，"
            "抛光的大理石地板有着美丽而"
            "耀眼的设计。");
    SetExits( ([
                "east" : "/domains/town/room/mansion_dhall3"
                ]) );
}
void init(){
    ::init();
}
