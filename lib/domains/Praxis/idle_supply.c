inherit "/lib/std/room";

void init() {
    ::init();
    add_action("go_north", "north");
}

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "霍勒斯冒险者杂货店");
    SetLong(
            "欢迎来到霍勒斯冒险者杂货店！\n"
            "霍勒斯在他营业时买卖冒险者们创造和发现的物品。"
            "商店朝南通往博克拉路。"
            "北边有一条由魔法力场守卫的通道。");
    SetItems(
            (["shop" : "你可以在这里买卖物品。",
             "passage" : "霍勒斯把待售的物品放在后面。",
             "road" : "博克拉路。"]) );
    SetExits( 
            (["south"	: "/domains/Praxis/e_boc_la2"]) );
    SetProperty("no castle", 1);
}

void reset() {
    ::reset();
    if(!present("horace")) 
        new("/domains/Praxis/obj/mon/horace")->move(this_object());
}

int go_north() {
    if(this_player()->query_position() == "player" ||
            this_player()->query_position() == "high mortal") {
        write("霍勒斯的魔法阻止了你。");
        say(this_player()->query_cap_name()+"被霍勒斯的魔法阻止了。",
                this_player());
        return 1;
    }
    write("你不受霍勒斯魔法的阻挡。");
    say(this_player()->query_cap_name()+"不受霍勒斯魔法的阻挡。",
            this_player());
    this_player()->eventMoveLiving("/domains/Praxis/storage", "north");
    return 1;
}

