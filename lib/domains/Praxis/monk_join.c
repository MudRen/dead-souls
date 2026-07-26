#include <lib.h>
int go_east();

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("become", "become");
    add_action("preview","preview");
}

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetProperty("no castle", 1);
    SetShort( "僧侣大厅入口");
    SetLong(
            "蜡烛照亮了修道院的各个房间。"
            "管理修道院的僧侣们住在这里，"
            "并将新信徒引入僧侣之道。"
            "东边的通道充满了闪烁的光芒。"
            "<preview>将告诉你如何成为僧侣。");
    SetItems(
            (["candles" : "它们遍布修道院各处。",
             "candle" : "它燃烧得很亮，帮助照亮房间。",
             "monk" : "她正平静地四处走动。",
             "passage" : "你感觉到只有僧侣才能通过那条路。"]) );
    SetExits( 
            (["down" : "/domains/Praxis/stairs"]) );
    AddExit("east","/domains/Praxis/monk_hall",(:go_east:));
}

int preview() {
    if(this_player()->query_class() != "explorer") {
        message("info", "这不适合你。", this_player());
        return 1;
    }
    say(this_player()->query_cap_name()+"想要了解僧侣。",
            this_player());
    message("info", "欢迎，探索者！", this_player());
    message("info", "僧侣由许多不同信仰但同样虔诚的人组成，"
            "他们都信仰唯一的善良之神，并致力于圣战以对抗"
            "任何地方的邪恶。他们对信仰近乎狂热。"
            "要成为僧侣，输入 <become monk>。", this_player());
    return 1;
}

int become(string str) {
    if(!str) {
        notify_fail("成为什么？\n");
        return 0;
    }
    if(str != "monk") {
        notify_fail("你不能在这里成为那个。\n");
        return 0;
    }
    if(this_player()->query_class() != "explorer") {
        message("my_action", "你太老了，现在不能开始学习我们的方式！", this_player());
        return 1;
    }
    message("my_action", "大领主高阶女祭司将你引入僧侣职业。", this_player());
    message("other_action", this_player()->query_cap_name()+"成为了一名僧侣。",
            this_object(), ({ this_player() }));
    this_player()->SetClass("monk");
    this_player()->setenv("TITLE", "$N the novice monk");
    this_player()->init_skills("monk");
    this_player()->setenv("start", "/domains/Praxis/monk_hall");
    return 1;
}

int go_east() {
    if(creatorp(this_player())){
        write("强大的不朽者总是欢迎来到这座谦卑的修道院。");
        return 1;
    } else
        if(this_player()->query_class() != "monk") {
            write("你无法穿透阻挡通道的力场。");
            say(this_player()->query_cap_name()+"试图进入僧侣圣地，但失败了。", this_player());
            return 0;
        }
    return 1;
}


