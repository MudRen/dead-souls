#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("read", "read");
}

void create() {
    ::create();
    SetProperties( ([ "light": 3, "indoors" : 1, "no castle" : 1 ]) );
    SetShort( "最后的龙餐厅");
    SetLong(
            "欢迎来到最后的龙餐厅！\n"
            "最后的龙餐厅是普拉克西斯最好的美食之家！"
            "气氛活跃而友好，服务也是如此。"
            "餐厅本身是一座精心打磨和维护的橡木建筑。"
            "墙上展示着菜单，女服务员在的时候会很乐意为你服务。"
            "南边是太阳巷。" );
    SetItems(
            (["restaurant" : "最后的龙餐厅，普拉克西斯美食之家。",
             "wall" : "菜单张贴在那里。",
             "menu" : "如果你愿意，可以阅读它。"]) );
    SetExits( 
            (["north" : "/domains/Praxis/sun2"]) );
}

void reset() {
    ::reset();
    if(!present("waitress")) 
        new("/domains/Praxis/obj/mon/waitress")->move(this_object());
}

int read(string str) {
    object ob;
    int i;

    ob = present("waitress");
    if(!ob) {
        write("你没法看菜单，上面溅满了鲜血。");
        return 1;
    }
    write("最后的龙餐厅供应以下美食。");
    write("--------------------------------------------------------------------");
    write("普拉克西斯龙虾\t\t\t"+ ob->get_price("lobster") + " 金币");
    write("一盘海虫\t\t\t"+ob->get_price("worms")+" 金币");
    write("一份鱼\t\t\t"+ob->get_price("fish")+" 金币");
    write("一些薯条\t\t\t"+ ob->get_price("fries")+" 金币");
    write("-----------------------------------------------------------");
    write("<buy 菜品名> 可以购买食物。");
    return 1;
}

