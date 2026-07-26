#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(20);
    SetShort("楼梯间");
    SetLong("你站在楼梯间的平台上。楼梯向上和向下延伸，不过向上的楼梯被绳子拦住了，无法通行。闪烁的荧光灯让人难以看清下面有什么。向上的楼梯绳子上挂着一块告示牌。");
    SetItems(([
                ({"stairs","flight","flight of stairs"}) : "楼梯是混凝土建造的，似乎是大楼地基的一部分，看起来相当坚固。",
                "landing" : "这是连接上下楼梯的平台。",
                "rope" : "粗大的黄色施工绳。向上的楼梯上绑了很多绳子，阻止你通行。上面挂着一块告示牌。",
                ({"light","lights","fluorescent lights"}) : "廉价的照明设备，似乎不太好用。闪烁的灯光偶尔将平台照成橙色，然后又恢复白色。",
                "sign" : "这是一块挂在被绳子拦住的楼梯上的手写纸板告示牌。"]));
    SetExits(([
                "north" : "/domains/campus/room/corridor3",
                "down" : "/domains/campus/room/basement" 
                ]));
    SetDoor("north","/domains/campus/doors/top_stairs");
    SetProperty("no attack", 1);
}
void init(){
    ::init();
    add_action("r_sign","read");
    add_action("untie_r","untie");
}
int r_sign(string str){
    if(str=="sign" || str=="cardboard sign"){
        write("告示牌上写着：\n"+
                "警告！二楼正在施工，禁止通行！\n");
        say(this_player()->GetName()+" read the sign.\n");
        return 1;
    }
}
int untie_r(string str){
    if(str=="rope" || str=="yellow rope"){
        write("The rope is quite firmly tied. You fail.\n");
        say(this_player()->GetName()+" fails to untie the rope.\n");
        return 1;
    }
}
