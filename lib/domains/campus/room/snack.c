#include <lib.h>
#include <dirs.h>
#include <message_class.h>
inherit LIB_ROOM;

int eventReadMenu(string str);
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("校园快餐吧");
    SetLong("你在一个铺着油毡瓷砖的小房间里，明亮的荧光灯照着。两张桌子周围摆着几把看起来不太舒服的椅子，北墙上嵌着一个吧台，吧台后面站着一名餐饮服务员。吧台旁边的墙上挂着一份菜单。主走廊在南边。");
    SetItems(([
                "menu": "这里提供的快餐菜单。",
                "sign":"快餐吧上方的招牌。",
                ({"tile","tiles","floor","linoleum"}):"这些在这里是因为不信任你能把食物远离地毯。",
                ({"chair","chairs","table","table"}):"象征性的家具，不太实用，看起来也不太舒服。显然，并不指望你在这里逗留。",
                "bar" : "实际上是嵌在墙上的一个窗口，将快餐吧与相邻的厨房连接起来。",
                ({"wall","walls"}) : "墙壁漆成蓝白两色，是学校的颜色。相当不美观，颇有机构风格。",
                "hallway" : "行政楼主走廊在南边。",
                ({"light","lights","fluorescent lights","fluorescents"}) : "廉价的标准照明。和所有荧光灯一样，这些灯让一切看起来都不太好看，带着病态的感觉。",
                "employee" : "一个薪水低、不被赏识、心怀怨恨的国家公务员。毫不意外。",
                ]));
    SetExits( ([
                "south" : "/domains/campus/room/corridor3.c",
                ]) );
    SetRead("menu", (: eventReadMenu :));
    SetInventory(([
                "/domains/campus/npc/gloria.c" : ({60, 1}) ]));
    SetProperty("no attack", 1);
}
int eventReadMenu(string str){
    write("\n"+
            "1) 火腿三明治：2 美元\n"+
        "2) 汉堡包：4 美元\n"+
        "3) 今日沙拉：3 美元\n\n"+
        "饮品：\n"+
        "1) 牛奶：1 美元\n"+
        "2) 佳得乐：2 美元\n");
    return 1;
}
void init(){
    ::init();
}
