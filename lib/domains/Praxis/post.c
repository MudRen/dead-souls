#include <lib.h>
#include <objects.h>
#include <post.h>

inherit LIB_ROOM;

void init() {
    object ob;

    ::init();
    if(!living(this_player()) || !interactive(this_player())) 
        this_player()->eventMoveLiving("/domains/Praxis/alley1", "north");
    add_action("mail", "mail");
}

void create() {
    ::create();
    SetShort( "普瑞克斯邮局");
    SetLong(
            "欢迎来到普瑞克斯邮局！\n"
            "普瑞克斯邮局是一栋别致的白漆建筑。由于所有顾客都在地板上行走，"
            "地板是磨损的木头。红色的装饰线条沿着墙壁，远处角落的窗户"
            "透进一丝微风。"
            "人们来这里阅读和发送邮件。输入<mail>访问你的邮箱，"
            "或输入<mail name>向玩家name发送邮件。"
            "梦魇邮局运行在跨MUD游戏系统上，意味着你可以向系统上任何其他MUD游戏的玩家发送邮件。"
            "输入<muds>查看系统上有哪些MUD游戏。可用的群组可以通过在%提示符下输入<g>来访问。"    );
    SetProperty("no castle", 1);
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetItems( ([ "list" : "你可以在邮局使用的命令列表。"]) );
    //exit changed by drakken 17.aug
    AddExit("north","/domains/Praxis/alley1",(: this_object(),"more" :) );
    SetProperty("no attack", 1);
    SetProperty("no steal", 1);
}

int mail(string str) {
    object ob;

    if(this_player()->query_name() == "guest") {
        notify_fail("游客不能使用邮件系统。\n");
        return 0;
    }
    ob = new(OB_POSTAL);
    ob->move(this_player());
    ob->start_post(str);
    return 1;
}

int more() {
    object ob;

    if(!(ob = present(POSTAL_ID, this_player()))) return 1;
    ob->destruct();
    return 1;
}

