#include <lib.h>

inherit LIB_ROOM;

int dug;
string orig_long, dug_long;
string is_dug();

void init() {
    ::init();
    add_action("read", "read");
    add_action("dig", "dig");
}

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("no castle", 1);
    SetShort( "西大道中段");
    SetLong( (: is_dug :));
    SetNoClean(1);
    SetItems(
            (["road" : "路边堆积着一堆松散的泥土。",
             "dirt" : "非常松散。",
             "hut " : "看起来非常神秘。",
             "sign" : "识字的人真是太幸运了！",
             "mound" : (: this_object(), "look_at_mound" :) ]) );
    SetSkyDomain("town");
    SetExits( 
            (["north" : "/domains/Praxis/west_road3",
             "south" : "/domains/Praxis/west_road1",
             "east" : "/domains/Praxis/medium"]) );
    dug = 0;
}

void reset() {
    ::reset();
    if(!dug) return;
    dug = 0;
    RemoveItem("hole");
    RemoveExit("down");
    call_other("/domains/Praxis/hole", "fixing_a_hole");
}

void look_at_mound() {
    if(!dug) write("看起来好像有人在那里挖了一个洞，然后又把它填回去了。");
    else write("这是从旁边的洞里挖出来的一堆泥土。");
}

int dig() {
    if(!present("shovel", this_player()) && !present("spade", this_player())) {
        notify_fail("你没有可以挖掘的工具！\n");
        return 0;
    }
    if(dug) {
        notify_fail("你要在哪里挖？\n");
        return 0;
    }
    write("你挖开土堆，露出了一个洞。");
    say(this_player()->query_cap_name()+"挖开了土堆，露出了一个洞。", this_player());
    dug = 1;
    AddItem("hole", "路边土堆旁有人刚刚挖出的洞。");    AddExit( "down", "/domains/Praxis/hole");

    call_other("/domains/Praxis/hole", "digging");
    return 1;
}

int query_dug() { return dug; }

int read(string str) {
    if(str != "sign" && str != "door") {
        notify_fail("读什么？\n");
        return 0;
    }
    write("莫拉的神秘学之屋。\n"
            "了解你或其他人今天的星座运势。");
    return 1;
}

string is_dug() {
    if(!dug) return "你正站在西大道的中段，道路两旁排列着乡村小屋。"
        "东侧的一间小屋外面挂着一块牌子。一堆松散的泥土覆盖了"
            "道路西侧的部分区域。";
    else return "你正站在西大道的中段，道路两旁排列着乡村小屋。"
        "东侧的一间小屋外面挂着一块牌子。道路西侧最近被挖出了"
            "一个洞。";
}
