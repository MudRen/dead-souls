#include <lib.h>
#include <daemons.h>
inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("消息接收室");
    SetLong("这是一个用于接收NPC特定消息的房间。主要用于调试目的，对正常的MUD运行并不重要。");
    SetExits(([
                "west" : "/secure/room/network",
                ]));

}
int CanReceive(object ob) {
    if( !archp(ob) ){
        message("info","消息接收室仅限管理员使用，抱歉。",ob);
        return 0;
    }
    return 1;
}
void init(){
    ::init();
}
