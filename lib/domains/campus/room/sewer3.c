#include <lib.h>
#include <damage_types.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(20);
    SetShort("维修管道");
    SetLong("这是一个狭窄的区域，连接着上方的地面和下方的下水道。这里拥挤、肮脏，对大多数类人生物来说不是一个友好的地方。光线似乎从上方的排水格栅射入。");
    SetItems( ([ ({"tube","service tube"}) : "你在维修管道里。这里污浊、黑暗、炎热。",
                ({"sewer","sewer system"}) : "虽然明显维护良好且是现代建筑，但这仍然是下水道隧道，对人类的舒适度很不友好。",
                "air" : "空气中弥漫着腐烂废物的恶臭。",
                "light" : "光线不多，你无法分辨是阳光还是灯光，但它让你能看得更清楚一些。",
                ]) );
    SetExits(([
                "down" : "/domains/campus/room/sewer2",
                "up" : "/domains/campus/room/south_road2",
                ]));
    SetSmell( ([ "default" : "污水和废物的恶臭弥漫在这里。"]) );
    SetListen("default","你听到滴水的微弱回声。");
    SetDoor("up","/domains/campus/doors/grate");
}

void init(){
    ::init();
}
