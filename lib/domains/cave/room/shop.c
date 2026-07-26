#include <lib.h>
inherit LIB_SHOP;

int read_sign();
protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("杂货店");
    SetLong("这是当地的杂货店。你可以在这里买卖物品。墙上挂着一个牌子，解释如何交易。试试'read sign'。储藏室在下面。");
    SetItems(([
                ({"store","shop","place"}) : "这是当地的商店。",
                ({ "sign" ,"sign on the wall" }) : "墙上的一个牌子，用来阅读的。",
                ]));
    SetExits( ([
                "south" : "/domains/cave/room/cavepass9",
                "down" : "/domains/cave/room/shop2.c",
                ]) );
    SetInventory(([
                "/domains/cave/npc/gorm" : 1,
                "/domains/cave/obj/bbucket" : 1,
                ]));
    SetRead("sign", (: read_sign :) );
}

int read_sign(){
    write("如何在这里交易\n");
    write("list : 获取奥蒂克出售的所有物品列表");
    write("appraise <物品> : 让奥蒂克告诉你他愿意为你的物品付多少钱");
    write("price <物品> : 询问奥蒂克他的物品价格");
    write("show <物品> : 让奥蒂克给你看看他的物品\n");
    write("\nbuy <物品> from otik\nsell <物品> to otik\n");
    write("只收现金！");
    return 1;
}
void init(){
    ::init();
}
