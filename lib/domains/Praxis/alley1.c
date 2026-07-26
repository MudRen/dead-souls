#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort("一条狭窄的小巷");
    SetSmell( "default", "淡淡的垃圾臭味扑面而来。");
    SetLong(
            "你发现自己在一条通往中心路的小土路上。"
            "这条土路偶尔会被一些不太体贴的普拉克西斯市民的垃圾弄得杂乱。"
            "当地的邮局在南边，北边你可以看到一座作为普拉克西斯银行的大型建筑。");
    SetItems(
            (["path" : "一条从中心路延伸出来的小土路。",
             "bank" :"普拉克西斯银行是一家非常著名的机构。",
             ({"office", "post", "post office"}) : "你可以在这里收发邮件，"
             "也可以发给其他泥潭的人。",
             "alley" : "小巷是一条非常小的土路。"]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "west" : "/domains/Praxis/alley2",
                "east" : "/domains/Praxis/s_centre2",
                ]) );
}
void init(){
    ::init();
}
