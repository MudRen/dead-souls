#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("go_north", "go");
}

void create() {
    ::create();
    SetProperties( ([ "light" : 2, "indoors" : 1, "no castle" : 1 ]) );
    SetShort("霍勒斯综合杂货店");
    SetLong(
            "欢迎来到霍勒斯综合杂货店！\n"
            "霍勒斯杂货店是普拉克西斯迄今为止最大的商铺。"
            "它建立于很久以前，多年来赢得了极高的声誉。"
            "商店后方有一个长长的柜台，你经常可以看到霍勒斯本人"
            "站在那里与顾客讨价还价。两扇窗户装饰着商店的前墙，"
            "一扇欢快的红色大门让你回到主街。霍勒斯在他营业时"
            "买卖冒险者们创造和发现的物品。北边的通道由魔法力场守卫。");
    SetItems(
            (["shop" : "你可以在这里买卖物品。",
             "passage" : "霍勒斯把待售的物品放在后面。",
             "road" : "博克拉路。"]) );
    SetInventory(([
                "/domains/Praxis/obj/mon/horace" : 1,
                ]));
    SetExits( 
            (["south" : "/domains/Praxis/e_boc_la2"]) );
    SetProperty("no castle", 1);
}

void reset() {
    ::reset();
    if(!present("horace")) 
        new("/domains/Praxis/obj/mon/horace")->move(this_object());
}

int go_north(string str) {
    if(str !="north") return notify_fail("What?\n");
    if(!creatorp(this_player())) {
        message("my_action", "霍勒斯的魔法阻止了你。", this_player());
        message("other_action", this_player()->query_cap_name()+
                "被霍勒斯的魔法阻止了。", this_object(),
                ({ this_player() }));
        return 1;
    }
    message("other_action", this_player()->query_cap_name()+
            "不受霍勒斯魔法的阻挡。", this_object(),
            ({ this_player() }));
    this_player()->eventMoveLiving("/domains/Praxis/storage", "north");
    return 1;
}
