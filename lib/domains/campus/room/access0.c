#include <lib.h>
inherit LIB_ROOM;

int eventHopDown(){
    write("你跳进了洞里，注意到这里没有梯子可以爬回去。");
    say(this_player()->GetName()+"跳进了敞开的检修孔。",this_player());
    return 1;
}
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(16);
    SetShort("通道隧道");
    SetLong("你站在一个看起来是地下服务通道的地方。头顶的霓虹灯闪烁着，提供勉强够用的照明。空气潮湿、带着霉味，感觉好像多年来没有人经过这里。隧道从这里向南延伸。这似乎是隧道的北端。地板上有一个敞开的大检修孔。");
    SetItems(([
                ({"wall","walls","corridor","hall"}) : "这里厚实的金属墙壁上有伤痕，腐蚀严重。无论你在什么地方，它在遥远的过去都经历过重度使用。",
                ({"lights","light","neon lights"}) : "头顶的霓虹灯。它们似乎濒临损坏。",
                ({"floor","ground"}) : "地板由焊接在一起的金属板组成，带有凸起的防滑齿。",
                ({"cleat","cleats"}) : "地板上的小凸起，防止你滑倒。",
                ({"ladder","metal ladder"}) : "你在混凝土地板上和洞里看到生锈的螺栓，表明这里曾经有一个梯子。",
                ({"hole","manhole"}) : "这是地板上建造的开口，通往下方的任何地方。看起来曾经有一个金属梯子方便移动，但现在没有了，所以下去是单程的。",
                ]));
    AddExit("down","/domains/campus/room/sewer", (: eventHopDown :) );
    AddExit("south","/domains/campus/room/access5");
}
int CanReceive(object ob){
    if(ob && ob->GetRace() == "rodent"){
        message("info","你被灭鼠剂驱退了。",ob);
        return 0;
    }
    return ::CanReceive(ob);
}
void init(){
    ::init();
}
