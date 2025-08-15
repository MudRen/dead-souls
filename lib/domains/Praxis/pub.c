#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("read", "read");
}

void create() {
    ::create();
    SetProperties( ([ "light": 2, "indoors" : 1, "no castle" : 1 ]) );
    SetShort( "拉尔斯酒馆和酒吧");
    SetLong(
            "欢迎来到拉尔斯酒馆！\n"
            "拉尔斯酒馆是一家非常古老且口碑良好的酒馆。它最近重新装修过，"
            "你可以从房间里嘈杂的交谈声中看出生意正在好转。地板是抛光木材制成的，"
            "房间后面的柜台也是。梦魇世界不同地区的图画挂在墙上，"
            "还有一些这片土地上被通缉的盗贼的通缉海报。");
    SetItems(
            (["pub" : "普瑞克斯最热闹的地方。",
             "wall" : "墙上覆盖着各种图画。",
             ({ "posters", "poster", "wanted posters" }) :
             "通缉海报非常古老且脆弱。它们标记着这片土地上盗贼的面孔。",
             ({ "pictures" , "picture" }) :
             "这些图画是梦魇世界不同地区的，由村里一些有抱负的艺术家所绘制。",
             "bar" : "酒吧实际上就是拉尔斯酒馆。这是一个非常干净且经营良好的场所。",
             "counter" : "木制柜台位于房间后面，存放着拉尔斯的所有饮品。",
             "room" : "你在拉尔斯酒馆的主房间里。",
             "foo" : "bar",
             "tavern" : "酒馆是普瑞克斯的人们想要喝一杯或只是社交时去的地方。",
             "floor" : "地板由坚固的橡木制成。",
             "list" : "看起来像是饮品清单。阅读它看看有什么可用的。"]) );
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
        write("你无法阅读菜单，因为它溅满了鲜血。");
        return 1;
    }
    message("Ninfo", "拉尔斯酒馆供应以下经典饮品！\n", this_player());
    message("Ninfo", "-----------------------------------------------------------\n", this_player());
    message("Ninfo", "火焰呼吸者\t\t\t"+ ob->get_price("firebreather")+" 金币\n", this_player());
    message("Ninfo", "招牌特饮\t\t\t"+ob->get_price("special")+" 金币\n", this_player());
    message("Ninfo", "淡色麦芽酒\t\t\t"+ob->get_price("ale")+" 金币\n", this_player());
    message("Ninfo", "-----------------------------------------------------------\n", this_player());
    message("Ninfo", "<buy drink_name> 可以购买饮品。\n", this_player());
    return 1;
}









