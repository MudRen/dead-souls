#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(5);
    SetShort("隧道");
    SetLong("你在一条黑暗狭窄的地下隧道里。墙壁是裸露的岩石和泥土……仿佛隧道是从大地中开凿出来的。管道和电缆沿着南墙延伸，似乎发出低沉的嗡嗡声。东边你看到一堵假墙，通往虚拟校区行政楼的地下室。西边，隧道继续延伸入黑暗之中。");
    SetItems(([
                "tunnel" : "这显然是虚拟校区下方的一条隐藏隧道。这里极其阴森黑暗。",
                "walls" : "墙壁是裸露的泥土和岩石。看起来建造这条隧道的人非常匆忙。",
                ({"wall","south wall","southern wall"}) : "南墙上布满了粗大的电缆和金属管道，沿着墙壁向西延伸。",
                ({"rock","earth"}): "墙壁由这些东西组成……这是一个粗糙的挖掘。",
                ({"pipe","pipes","cable","cables"}): "这些粗大的管道和电缆似乎沿着墙壁输送电力。它们发出轻微的嗡嗡声。",
                "darkness":"黑暗深沉。黑暗浓厚。这里是光明的缺失，到处都是。",
                ]));
    SetListen("default","You hear faint echoes of dripping water.");
    SetExits(([
                "east" : "/domains/campus/room/basement2",
                "west" : "/domains/campus/room/tunnel2"]));
    SetProperty("no attack", 1);
    SetCoordinates("4003,4000,-1");
}
void init(){
    ::init();
    AddListen(({"pipe","pipes","wall","cables","cable"}) , "The pipes and "+
            "cables throb with some unknown power...emitting an eerie hum.");
}
