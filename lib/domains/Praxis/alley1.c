#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort("一条狭窄的小巷");
    SetSmell( "default", "一股淡淡的垃圾臭味扑面而来。");
    SetLong(
            "你发现自己身处一条连接中心大道的小土路上。这是一条土路，"
            "偶尔被普瑞克斯一些不太文明的市民丢弃的垃圾所堵塞。"
            "当地邮局在南边，北边你可以看到一栋作为普瑞克斯银行的大楼。");
    SetItems( 
            (["path" : "这是一条连接中心大道的小土路。",
             "bank" :"普瑞克斯银行是一家非常知名的机构。",
             ({"office", "post", "post office"}) : "你可以在这里或其他泥巴游戏上给其他人发送和接收邮件。",
             "alley" : "小巷是一条很小的土路。"]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "west" : "/domains/Praxis/alley2",
                "east" : "/domains/Praxis/s_centre2",
                ]) );
}
void init(){
    ::init();
}
