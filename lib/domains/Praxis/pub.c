#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("read", "read");
}

void create() {
    ::create();
    SetProperties( ([ "light": 2, "indoors" : 1, "no castle" : 1 ]) );
    SetShort( "拉斯酒馆");
    SetLong(
            "欢迎来到拉斯酒馆！\n"
            "拉斯酒馆是一家历史悠久、久负盛名的酒吧。它最近刚"
            "经过翻修，从房间里此起彼伏的交谈声就能看出生意"
            "日渐兴隆。地板由抛光木材铺成，房间后方的吧台"
            "也是如此。墙上挂着噩梦世界各个地方的图画，"
            "还有一些被通缉的恶徒的悬赏告示。");
    SetItems(
            (["pub" : "普拉克西斯最热闹的地方。",
             "wall" : "墙上挂满了各种图画。",
             ({ "posters", "poster", "wanted posters" }) :
             "悬赏告示已经非常老旧且易碎。上面描绘着这片土地上"
             "恶徒的面容。",
             ({ "pictures" , "picture" }) :
             "这些图画描绘了噩梦世界的各个地方，由村庄里几位"
             "有抱负的艺术家所绘。",
             "bar" : "酒吧就是拉斯酒馆。这是一家非常干净、"
             "经营有方的场所。",
             "counter" : "木质吧台立在房间后方，上面摆满了"
             "拉斯的各种饮品。",
             "room" : "你正站在拉斯酒馆的主厅里。",
             "foo" : "bar",
             "tavern" : "酒馆是普拉克西斯的人们想喝一杯或"
             "社交聚会时的去处。",
             "floor" : "地板由实心橡木铺成。",
             "list" : "看起来是一份饮品清单。读一读看看有什么。"]) );
    SetExits( 
            (["north" : "/domains/Praxis/w_boc_la1",
             "east" : "/domains/Praxis/s_centre1"]) );
    SetProperties( ([  "no castle": 1, "no attack" : 1 ]) );
}

void reset() {
    ::reset();
    if(!present("list")) 
        //new("std/obj/player_list")->move(this_object());
        if(!present("lars")) 
            new("/domains/Praxis/obj/mon/lars")->move(this_object());
}

int read(string str) {
    object ob;
    int i;

    ob = present("lars");
    if(!ob) {
        write("你没法看菜单，上面溅满了鲜血。");
        return 1;
    }
    message("Ninfo", "拉斯酒吧供应以下经典饮品！\n", this_player());
    message("Ninfo", "-----------------------------------------------------------\n", this_player());
    message("Ninfo", "烈焰呼吸\t\t\t"+ ob->get_price("firebreather")+" 金币\n", this_player());
    message("Ninfo", "本店特调\t\t\t"+ob->get_price("special")+" 金币\n", this_player());
    message("Ninfo", "淡色麦酒\t\t\t"+ob->get_price("ale")+" 金币\n", this_player());
    message("Ninfo", "-----------------------------------------------------------\n", this_player());
    message("Ninfo", "<buy 饮品名> 可以购买一杯饮品。\n", this_player());
    return 1;
}









