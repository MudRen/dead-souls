#include <lib.h>

inherit LIB_ROOM;

varargs string readMenu() {
    string ret = "\tStein of Guinness\t\t\t1 gold\n"+
        "\tBottle of wine\t\t\t\t2 gold\n"+
        "\tBottle of whiskey\t\t\t3 gold\n";
    return ret;
}

void create(){
    ::create();
    SetAmbientLight(30);
    SetShort("哈里酒吧");
    SetLong("哈里酒吧是一个简单的地方，孤独的水手们在这里消磨时光，谈论他们的家乡。这里以供应烈酒和粗鲁的顾客闻名，但地方干净整洁，没什么东西可以砸在别人头上。墙上的菜单列出了可用的饮品。西边似乎有个后屋。");
    SetClimate("indoors");
    SetItems( ([
                ({"wall", "walls"}) : "要是墙壁能说话就好了，对吧？",
                "menu" : "一份你可以阅读的菜单。奇怪的是，它的标志是一颗插在棍子上的狼头。",
                ({"room","back room"}) : "也许是个储藏区。",
                "harry" : "自从那件假戒指的事之后，就没人见过哈里了。",
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
