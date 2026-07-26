#include <lib.h>
inherit LIB_SHOP;
int read_sign();

protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("校园书店");
    SetLong("这是虚拟校区书店。这是一个相当小的地方，实际上可供出售的书籍很少，因为校园尚未开学。不过，这里有各种实用物品可供选购，你可以输入 'list' 命令来浏览。储藏室在楼上。柜台后面的墙上有一块告示牌。");
    SetItems(([
                ({"store","bookstore","place"}) : "这是虚拟校区书店。",
                "books" : "还没有书呢。你刚才没注意听吗？",
                ({"assortment","items","stuff"}) : "输入 list 来浏览你可以购买的物品。",
                "counter" : "一个廉价的仿木纹柜台，设计目的是让你更方便地掏钱。",
                "sign" : "墙上的一块告示牌，可以阅读。",
                ]));
    SetExits( ([
                "south" : "/domains/campus/room/corridor4",
                "up" : "/domains/campus/room/bookstore2.c",
                ]) );
    SetInventory(([
                "/domains/campus/obj/bbucket" : 1,
                "/domains/campus/obj/register" : 1,
                /*
                 * Note: kim has to load *after* the cash register
                 * in order to guard it!
                 */
                "/domains/campus/npc/kim" : 1,
                ]));
    SetRead("sign", (: read_sign :) );
    SetProperty("no attack", 1);
}

void init(){
    ::init();
    if(!present("bookstore employee",this_object())){
        new("/domains/campus/npc/kim")->eventMove(this_object());
    }
}

int read_sign(){
    write("如何在此处交易\n");
    write("list ：获取Kim出售的所有物品列表");
    write("appraise <物品> ：请Kim告诉你她愿意为你的物品支付多少");
    write("price <物品> ：询问Kim她的物品价格");
    write("show <物品> ：请Kim展示她的物品供你仔细查看\n");
    write("\nbuy <物品> from kim\nsell <物品> to kim\n");
    write("仅收现金美元！");
    return 1;
}
