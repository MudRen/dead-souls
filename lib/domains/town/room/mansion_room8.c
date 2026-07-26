#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("大舞厅");
    SetLong("这个巨大的房间在规模和装饰上都令人叹为观止。作为庄园的核心，这个舞厅可以轻松容纳数百位宾客。拱形天花板高达数十英尺，抛光的大理石地板上有着美丽而耀眼的图案。");
    SetExits( ([
                "east" : "/domains/town/room/mansion_dhall3"
                ]) );
}
void init(){
    ::init();
}
