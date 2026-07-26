#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("普通之地");
    SetLong("这是一个极其普通、空白的地方。");
}
void init(){
    ::init();
}
