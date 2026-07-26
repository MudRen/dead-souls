#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(5);
    SetShort("隧道");
    SetLong("你在一条黑暗狭窄的地下隧道里。墙壁是裸露的岩石和泥土……仿佛隧道是从大地中开凿出来的。管道和电缆沿着南墙延伸，似乎发出低沉的嗡嗡声。西边和东边，你可以看到一些光线。");
    SetListen("default","你听到滴水的微弱回声。");
    SetItems(([
                "tunnel" : "这显然是虚拟校区下方的一条隐藏隧道。这里极其阴森黑暗。",
                "walls" : "墙壁是裸露的泥土和岩石。看起来建造这条隧道的人非常匆忙。",
                ({"wall","south wall","southern wall"}) : "南墙上布满了粗大的电缆和金属管道。",
                ({"rock","earth"}): "墙壁由这些东西组成……这是一个粗糙的挖掘。",
                "darkness":"黑暗深沉。黑暗浓厚。这里是光明的缺失，到处都是。",
                ]));
    SetExits(([
                "east" : "/domains/campus/room/tunnel",
                "west" : "/domains/campus/room/access7"]));
    SetProperty("no attack", 1);
}
void init(){
    ::init();
    AddListen(({"pipe","pipes","wall","cables","cable"}) , "The pipes and "+
            "cables throb with some unknown power...emitting an eerie hum.");
}
