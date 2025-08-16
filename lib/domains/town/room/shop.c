#include <lib.h>
inherit LIB_SHOP;

int read_sign();
protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("杂货店");
    SetLong("这是本地的杂货店。你可以在这里买卖物品。墙上挂着一个标牌，解释这里如何运作。尝试使用'read sign'命令。东村路在南边。储藏室在下面。");
    SetItems(([
                ({"store","shop","place"}) : "这是本地的商店。",
                ({ "sign" ,"sign on the wall" }): "墙上的一个标牌，用来阅读。",
                ]));
    SetExits( ([
                "south" : "/domains/town/room/vill_road2",
                "down" : "/domains/town/room/shop2.c",
                ]) );
    SetInventory(([
                "/domains/town/obj/bbucket" : 1,
                "/domains/town/npc/otik" : ({60, 1}),
                ]));
    SetRead("sign", (: read_sign :) );

    SetDoor("down", "/domains/town/doors/otik_d.c");

}
int read_sign(){
    write("如何在这里做生意\n");
    write("list : 获取奥蒂克出售的所有物品清单");
    write("appraise <物品> : 让奥蒂克告诉你他会为你的物品支付多少钱");
    write("price <物品> : 询问奥蒂克他的物品价格");
    write("show <物品> : 让奥蒂克给你更近距离地看看他的物品\n");
    write("\nbuy <物品> from otik\nsell <物品> to otik\n");
    write("只收现金！");
    return 1;
}
void init(){
    ::init();
}
