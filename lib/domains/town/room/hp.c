#include <lib.h>

inherit LIB_ROOM;

varargs string readMenu() {
    string ret = "\t吉尼斯啤酒杯\t\t\t1金币\n"+
        "\t葡萄酒瓶\t\t\t\t2金币\n"+
        "\t威士忌酒瓶\t\t\t3金币\n";
    return ret;
}

void create(){
    ::create();
    SetAmbientLight(30);
    SetShort("哈里酒馆");
    SetLong("哈里酒馆是一个简单的地方，孤独的水手们在这里消磨时间，谈论他们的家乡。以供应烈酒和客人而闻名，这个地方干净整洁，没什么东西可以砸在某人头上。墙上的菜单列出了可用的饮品。西边似乎有某种后室。");
    SetClimate("indoors");
    SetItems( ([
                ({"wall", "walls"}) : "要是它们能说话就好了，是吧？",
                "menu" : "一个你可以阅读的菜单。奇怪的是，它的标志是一个插在棍子上的狼头。"
                ({"room","back room"}) : "也许是个储藏区。"
                "harry" : "自从那个摇摆戒指事件后，就没人见过哈里了。"
                ]) );
    SetSkyDomain("town");
    SetRead("menu", (: readMenu :) );
    SetInventory(([
                "/domains/town/npc/brandy" : 1,
                ]) );
    SetExits( ([
                "east" : "/domains/town/room/bwalk1.c",
                ]) );
}

void init(){
    ::init();
}
