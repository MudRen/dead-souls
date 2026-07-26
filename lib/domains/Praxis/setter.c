//      /d/standard/setter.c
//      Starting room for new characters choosing races
//      from the Nightmare Mudlib
//      created by Shadowwolf@Nightmare july 1992
//      modified by Descartes of Borg for the race daemon 10 june 1993

#include <lib.h>
#include ROOMS_H
#include <daemons.h>

inherit LIB_ROOM;

void do_rolls();

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetLong(
            "你在一个既无限又没有维度的小盒子里。"
            "现实是黑暗的，没有物质。你正在被创造。"
            "你直觉到一份你可能成为的种族列表，甚至可以阅读它。"
            "一旦你选择了种族，你就可以开始在噩梦世界的旅程了！"
            "输入 <read list> 查看种族列表。");
    SetItems(
            (["room" : "你将从中诞生进入噩梦世界的虚无。",
             "list" : "噩梦世界中存在的种族列表。"]) );
}

void init() {
    ::init();
    add_action("read", "read");
    add_action("pick","pick");
    if (this_player()->query_exp() != 0) {
        write("\n欢迎来到噩梦世界！\n"
                "请为自己选择一个种族。你的种族决定了你的主要"
                "基因属性：力量、智力、敏捷、体质和魅力。");
        this_player()->set_rolls(0);
    }
}
int pick(string str) {
    string *which;
    mapping borg;
    int tmp, i;
    string Class;

    Class = "child";
    if(!str) {
        write("要选择种族，输入 \"pick 种族名\"，其中种族名是你要选择的种族。");
        return 1;
    }
    str = lower_case(str);
    if(str == "satyr" &&
            this_player()->query_gender() != "male") {
        write("你必须是男性才能成为萨特！\n重新选择。");
        return 1;
    }
    else if(str == "nymph" && this_player()->query_gender()
            != "female") {
        write("你必须是女性才能成为宁芙！\n重新选择。");
        return 1;
    }
    if(member_array(str, RACES_D->query_races()) == -1) {
        write("你必须从列表中选择一个种族！\n输入 <read list>\n");
        return 1;
    }
    this_player()->SetRace(str);
    this_player()->new_body();
    this_player()->SetClass(Class);
    if( this_player()->query_gender() == "male") this_player()->setenv("TITLE", "Newbie $N the boy");
    else this_player()->setenv("TITLE", "Newbie $N the girl");
    this_player()->init_skills(Class);
    write("你可以掷骰三次来决定你的属性。");
    write("你将在即将选择的职业大厅里进行这个操作。");
    do_rolls();
    write("你现在被传送到村庄广场。");
    this_player()->eventMoveLiving(ROOM_START);
    return 1;
}

void do_rolls() {
    string *which;
    mapping borg;
    int i, tmp;

    if(this_player()->query_rolls() >3) {
        write("你不能再掷骰了。");
        return;
    }
    write("你掷骰决定了你的属性。");
    for(i=0, tmp=sizeof(which=keys(borg=RACES_D->do_rolls(this_player()->query_race()))); i<tmp; i++) 
        this_player()->SetStat(which[i], borg[which[i]]);
    this_player()->set_rolls(this_player()->query_rolls()+1);
    return;
}

int read(string str) {
    string *res;
    int i, j, tmp;
    if(!str) {
        notify_fail("你想读什么？列表？\n");
        return 0;
    }
    if(str != "list") {
        notify_fail("这里没有那个可以阅读。\n");
        return 0;
    }
    write("以下是我们的世界中可用的种族：");
    write("-----------------------------------------------------------");
    message("Ninfo", format_page(RACES_D->query_races(), 4),
            this_player());
    write("----------------------------------------------------------");
    write("只有男性可以成为萨特，只有女性可以成为宁芙。");
    write("pick <种族> 将使你永远成为该种族的一员");
    write("输入 <help races> 获取更多信息。");
    return 1;
}
