#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( ([ "light" : 2, "indoors" : 1, "no castle" : 1 ]) );
    SetShort("霍勒斯综合杂货店");
    SetLong(
            "欢迎来到霍勒斯综合杂货店！\n"
            "霍勒斯在他营业时买卖冒险者们创造和发现的物品。"
            "商店朝南通往博克拉路。"
            "北边有一条由魔法力场守卫的通道。");
    SetItems(
            (["shop" : "你可以在这里买卖物品。",
             "passage" : "霍勒斯把待售的物品放在后面。",
             "road" : "博克拉路。"]) );
    SetExits( ([ "south" : "/domains/Praxis/e_boc_la2",
                "north" : "/domains/Praxis/storage" ]) );
    set_pre_exit_functions( ({ "north" }), ({ "go_north" }) );
    add_sky_event( (: "shop_closing" :) );
}

void reset() {
    ::reset();
    if(query_night()) return;
    if(!present("horace")) 
        new("/domains/Praxis/obj/mon/horace")->move(this_object());
}

string shop_long(string str) {
    if(query_night()) 
        return "霍勒斯的店已经关门了。";
}

void shop_closing(string str) {
    object ob;

    if(str == "night" && ob = present("horace", this_object()))
        ob->destruct();
    else if(str == "dawn" && !present("horace", this_object()))
        new("/domains/Praxis/obj/mon/horace")->move(this_object());
}

int go_north(string str) {
    if(!creatorp(this_player())) {
        message("my_action", "霍勒斯的魔法阻止了你。", this_player());
        message("other_action", this_player()->query_cap_name()+
                "被霍勒斯的魔法阻止了。", this_object(),
                ({ this_player() }));
        return 0;
    }
    message("other_action", this_player()->query_cap_name()+
            "不受霍勒斯魔法的阻挡。", this_object(),
            ({ this_player() }));
    return 1;
}
void init(){
    ::init();
}
