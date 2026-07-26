#include <lib.h>
#include <daemons.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("网络室");
    SetLong("这是所有网络消息的汇集处。这是一个极其嘈杂和不舒适的地方，"+
            "就像世界各地的网络室一样。它是为了调试和故障排除而存在的，"+
            "所以如果你不是在做这些，你可能应该离开。"+
            "管理员房间在上面。路由器室在南边。catch_tell室在东边。");
    SetExits( ([
                "south" : "/secure/room/router",
                "up" : "/secure/room/arch",
                "east" : "/domains/default/room/catchtell.c",
                ]) );

}
int CanReceive(object ob) {
    if( !archp(ob) ){
        message("info","网络室仅供管理员使用，抱歉。",ob);
        return 0;
    }
    return 1;
}
void init(){
    ::init();
}
