#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("当地酒馆");
    SetLong("你正在当地的酒馆里。你可以在这里点饮品和三明治：\n\n"+
            "\t顶级啤酒：\t\t\t\t10银币\n"
            "\t特色招牌：\t\t\t\t20银币\n"
            "\t喷火者：\t\t\t\t\t50银币\n"
            "\t山泉水：\t\t\t\t\t2银币\n"
            "\t普通咖啡：\t\t\t\t\t5银币\n"
            "\t进口浓缩咖啡：\t\t\t\t15银币\n"
            "\t火腿三明治：\t\t\t\t\t10银币\n\n\n"
            "要点一瓶水，请使用命令\"buy water from lars\"\n"
            "\n墙上挂着一幅装裱的肖像画。\n"
           );
    SetItems(([
                ({ "portrait", "framed portrait", "frame", "picture" }) : "这是一幅戏剧性的古老巨龙肖像，展现出极致的美丽与优雅。标题是\"戴拉斯：阿罗达利亚斯的后裔\".",
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
