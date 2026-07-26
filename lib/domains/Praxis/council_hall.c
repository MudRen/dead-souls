#include <lib.h>
#include ROOMS_H
#include <council.h>
#include <daemons.h>

inherit LIB_ROOM;

int CanReceive(object ob) {
    if((!previous_object()->is_player()) ||
            creatorp(previous_object()) ||
            (-1!=member_array(previous_object()->query_name(), COUNCIL)))
        return ::CanReceive(ob);
    message("my_action", "你不被允许进入议会厅。如果你是"
            "议会成员，请尝试按顺序联系尼尔森、律师和法律。", previous_object());
    return 0; 
}

void create() {
    object ob;

    ::create();
    SetProperties( (["light"       : 2, 
                "indoors"     : 1,
                "no attack"   : 1,
                "no steal"    : 1,
                "no magic"    : 1,
                "no teleport" : 1,
                "no castle"   : 1]) );
    SetShort( "议会私人会议厅");
    SetLong( "欢迎来到广场下方的洞穴。这是各职业议会的会议厅。" );
    SetExits( (["leave" : "/domains/Praxis/square"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "pipe dream board", "bulletin board"}) );
    ob->set_board_id("council_board");
    ob->set_max_posts(30);
    ob->set_edit_ok( ({"nialson"}) );
    ob->move(this_object());
    ob->SetShort( "避免职业战争的白日梦布告板");
    ob->SetLong( "这是一些考虑不周的威胁和有用的建议的集合，"
            "旨在增加信息的有序流动，降低玩家之间的紧张程度"
            "（至少对不朽者来说是这样）。");
    SetSearch("default", "哎呀，费迪南德大公的遗骸被藏在这里了！"
            "原来他遭遇了这样的事情。");
}

void init() {
    ::init();
    add_action("leave","leave");
}

int leave() {
    string verb;
    string *tmpstrs;
    int val;

    if( this_player()->query_disable() &&
            sizeof(this_player()->query_attackers()) ) {
        write("你不能在做其他事情的时候退出。");
        return 1; }
    if (creatorp(this_player()))
        this_player()->eventMoveLiving("/domains/Praxis/adv_inner", "leave");
    else
        this_player()->eventMoveLiving("/domains/Praxis/"+this_player()->query_class()+
                "_hall", "leave");
    return 1;
}
