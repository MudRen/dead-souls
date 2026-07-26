#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(16);
    SetShort("通道隧道");
    SetLong("你站在一个看起来是地下服务通道的地方。头顶的霓虹灯闪烁着，提供勉强够用的照明。空气潮湿、带着霉味，感觉好像多年来没有人经过这里。隧道从这里向南北延伸。");
    SetItems(([
                ({"wall","walls","corridor","hall"}) : "这里厚实的金属墙壁上有伤痕，腐蚀严重。无论你在什么地方，它在遥远的过去都经历过重度使用。",
                ({"lights","light","neon lights"}) : "头顶的霓虹灯。它们似乎濒临损坏。",
                ({"floor","ground"}) : "地板由焊接在一起的金属板组成，带有凸起的防滑齿。",
                ({"cleat","cleats"}) : "地板上的小凸起，防止你滑倒。",
                ]));
    SetEnters( ([ 
                ]) );
    AddExit("north","/domains/campus/room/access0");
    AddExit("south","/domains/campus/room/access6");
    SetInventory(([
                "/domains/campus/npc/rat" :1
                ]));
}

void init(){
    ::init();
}
