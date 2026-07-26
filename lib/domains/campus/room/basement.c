#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(29);
    SetShort("地下室");
    SetLong("你在LPC大学行政楼的地下室里。这里非常黑暗，相当潮湿。荧光灯似乎濒临完全损坏，只有一两盏忽明忽暗的灯勉强能看清东西。这里的空气潮湿、厚重、带着霉味。楼梯下面有一个小爬行空间可以进入，地下室向西延伸入黑暗之中。");
    SetItems(([
                "stairs" : "一段向上的楼梯。下面有一个爬行空间。",
                "basement" : "这是一个黑暗、令人毛骨悚然的地下室。",
                "building" : "你在LPC大学行政楼的地下室里。",
                ({"dark","darkness"})  : "到处都是黑暗。",
                ({"light","lighting","fluorescent lighting"}) : "这里的照明极其糟糕。灯光刚好够让你知道你不想在这里待太久。",
                "air" : "空气沉重，让人难以呼吸。很难想象谁会喜欢待在这里。",
                "crawlspace" : "看起来如果你真的想进去的话，也许能进入这个爬行空间。"]));
    SetInventory((["/domains/campus/npc/rat" : 1]));
    AddExit("up","/domains/campus/room/stairwell");
    AddExit("west","/domains/campus/room/basement2");
    AddEnter("crawlspace" , "/domains/campus/room/crawlspace");
    SetProperty("no attack", 1);
}

void init(){
    ::init();
}
