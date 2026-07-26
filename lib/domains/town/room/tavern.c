#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("当地酒馆");
    SetLong("你在当地酒馆里。你可以在这里点饮品和三明治：\n\n"+
            "\t一级麦酒：\t\t\t\t10 银币\n"
            "\t店家特调：\t\t\t\t20 银币\n"
            "\t烈焰之息：\t\t\t\t\t50 银币\n"
            "\t泉水：\t\t\t\t\t2 银币\n"
            "\t普通咖啡：\t\t\t\t\t5 银币\n"
            "\t进口浓缩咖啡：\t\t\t\t15 银币\n"
            "\t火腿三明治：\t\t\t\t\t10 银币\n\n\n"
            "要买一瓶水，请输入 \"buy water from lars\"\n"
            "\n墙上挂着一幅带框的肖像。\n"
           );
    SetItems(([
                ({ "portrait", "framed portrait", "frame", "picture" }) : "这是一幅气势恢宏的远古巨龙肖像，美丽而优雅。标题为 \"达拉斯：阿罗达利斯的继承者\"。",
                ]));
    SetInventory(([
                "/domains/town/obj/btable" : 1,
                "/domains/town/obj/bbucket" :1,
                "/domains/town/npc/lars" : ({ 60, 1})
                ]) );
    SetExits( ([
                "west" : "/domains/town/room/road",
                "out" : "/domains/town/room/road",
                ]) );
}
void init(){
    ::init();
}
