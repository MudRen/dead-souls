#include <lib.h>
inherit LIB_SHOP;

int read_sign();
protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("魔法商店");
    SetLong("这是当地的魔法商店。可以在这里买卖魔法物品。储藏室在楼上，城镇法师公会在南边。");
    SetItems(([
                ({"store","shop","place"}) : "这是当地的魔法商店。",
                ({ "sign" ,"sign on the wall" }): "墙上的一块标牌，用于阅读。",
                ]));
    SetExits( ([
                "south" : "/domains/town/room/magic_guild",
                "east" : "/domains/town/room/south_road1",
                "up" : "/domains/town/room/magic_shop2.c",
                ]) );
    SetRead("sign", (: read_sign :) );
    SetInventory( ([
                "/domains/town/npc/oana" : ({60, 1}),
                "/domains/town/obj/bbucket" : 1,
                ]) );
}
int read_sign(){
    write("如何在这里进行交易\n");
    write("list : 获取奥娜出售的所有物品列表");
    write("appraise <item> : 请奥娜告诉你她愿意为你的物品支付多少钱");
    write("price <item> : 询问奥娜她的物品价格");
    write("show <item> : 请奥娜让你更仔细地查看她的物品\n");
    write("\nbuy <item> from oana\nsell <item> to oana\n");
    write("显示的价格以银币为单位。");
    write("\n\n我们仍在建设中，所以这里");
    write("没有太多东西可买。但如果你愿意，你可以");
    write("向南去法师公会并加入！");

    return 1;
}
void init(){
    ::init();
}
