#include <lib.h>
inherit LIB_SHOP;

int read_sign();
protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("杂货店");
    SetLong("这里是当地的杂货店。你可以在这里买卖物品。墙上挂着一块告示牌，说明了如何操作。试试 'read sign'。东村路在南边，储藏室在下面。");
    SetItems(([
                ({"store","shop","place"}) : "这里是当地的商店。",
                ({ "sign" ,"sign on the wall" }): "墙上的一块告示牌，供人阅读。",
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
    write("HOW TO CONDUCT BUSINESS HERE\n");
    write("list : Get a list of all the items Otik has for sale");
    write("appraise <item> : Ask Otik to tell you how much he would pay you for your item");
    write("price <item> : Ask Otik the price of his item");
    write("show <item> : Ask Otik for a closer look at his item\n");
    write("\nbuy <item> from otik\nsell <item> to otik\n");
    write("Cash only!");
    return 1;
}
void init(){
    ::init();
}
