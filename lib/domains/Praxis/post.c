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
    SetShort( "普拉克西斯邮局");
    SetLong(
            "欢迎来到普拉克西斯邮局！\n"
            "普拉克西斯邮局是一座古色古香的白色建筑。地板因众多"
            "来往顾客的踩踏而磨损。红色的装饰线条沿着墙壁延伸，"
            "远处角落的窗户透进一丝微风。"
            "人们来这里阅读和发送邮件。输入 <mail> 打开你的邮箱，"
            "或 <mail 角色名> 向指定玩家发送邮件。"
            "噩梦邮局运行在互联泥系统上，意味着你可以向系统中"
            "其他任何泥潭的玩家发送邮件。"
            "输入 <muds> 查看系统中有哪些泥潭。可用的群组"
            "可以在 % 提示符下输入 <g> 来访问。"    );
    SetProperty("no castle", 1);
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetItems( ([ "list" : "一份你可以在邮局使用的命令列表。"]) );
    //exit changed by drakken 17.aug
    AddExit("north","/domains/Praxis/alley1",(: this_object(),"more" :) );
    SetProperty("no attack", 1);
    SetProperty("no steal", 1);
}

int mail(string str) {
    object ob;

    if(this_player()->query_name() == "guest") {
        notify_fail("Guest may not use the mailer.\n");
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

