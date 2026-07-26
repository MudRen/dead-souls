#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( (["light": 3, "no castle" : 1 ]));
    SetShort( "西部大公路");
    SetLong(
            "西部大公路向东西两个方向延伸，连接着山区与这片土地上"
            "众多的其他村庄。越往西走，空气变得越干燥。公路已经"
            "变得非常尘土飞扬，开始与大地融为一体，几乎难以辨认。"
            "望向达洛克山脉的另一边，你可以看到加吉普沙漠的起始之处。");
    SetItems(
            (["highway" : "一条连接西部山区与东部人口稠密城镇的繁忙土路。",
             "lands" : "你身处一片森林覆盖的山谷中，西边是达洛克山脉。",
             "mountains" : "达洛克山脉，邪恶哥布林的家园。",
             "mountain" : "特伦达尔山。",
             "daroq mountains" : "邪恶的哥布林生活在山脉中蜿蜒的隧道里。"]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "west" : "/domains/Praxis/highway3",
                "east" : "/domains/Praxis/highway1",
                ]) );
}

void reset() {
    ::reset();
    if(!present("bag")) 
        new("/domains/Praxis/obj/misc/bag")->move(this_object());
}
void init(){
    ::init();
}
