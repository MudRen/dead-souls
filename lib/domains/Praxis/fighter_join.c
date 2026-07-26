#include <lib.h>
int go_up();

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
    SetShort( "战士大厅");
    SetLong(
            "战士大厅装饰着华丽的挂毯，描绘着各种传统中"
            "战斗的男男女女。冒险的战士们聚集在螺旋楼梯底部"
            "讨论荣耀，楼梯通向天花板上一个被魔法照亮的洞口。"
            "年轻的战士们站在周围，希望能学习战士之道。"
            "年轻人可以<preview>了解成为战士是什么感觉。");
    SetItems(
            ([({"tapestry", "tapestries", "wall"}) : "墙上到处覆盖着"
             "来自各地最华丽的挂毯。你正在看的那幅描绘了"
             "一条龙和一个人类战士之间的英勇战斗。",
             ({"hole", "light", "opening", "ceiling"}) : "在天花板上，"
             "楼梯穿过一道神秘的光芒通向二楼。",
             "staircase" : "它穿过天花板的开口通往二楼。",
             "fighters" : "他们吵闹且令人讨厌。",
             ({"warriors", "young warriors"}) : "他们看起来茫然无知。"]) );
    SetExits(
            (["southeast" : "/domains/Praxis/s_centre4"]) );
    AddExit("up", "/domains/Praxis/fighter_hall", (:go_up:));
    SetListen("default", "战士们大喊大叫，吵闹得令人讨厌。");
}

int preview() {
    if(this_player()->query_class() != "explorer") {
        write("这不适合你。\n");
        return 1;
    }
    say(this_player()->query_cap_name()+"想要了解战士。",
            this_player());
    write("欢迎，探索者！");
    write("战士是唯一将战斗视为艺术形式的人。"
            "some are great knights who fight for good wherever "
            "they go.  Others might be considered quite fiendish in some circles. "
            "They therefore have no moral restrictions placed upon them. But "
            "they spend so much time learning the arts of combat, that they "
            "are almost entirely ignorant of the ways of magic.  To become "
            "a fighter, type <become fighter>.");
    return 1;
}

int become(string str) {
    if(!str) {
        notify_fail("成为什么？\n");
        return 0;
    }
    if(str != "fighter") {
        notify_fail("你不能在这里成为那个。\n");
        return 0;
    }
    if(this_player()->query_class() != "explorer") {
        write("你太老了，现在不能开始学习我们的方式！");
        return 1;
    }
    write("伟大的战士将你引入战士职业。");
    say(this_player()->query_cap_name()+"成为了一名战士。", this_player());
    this_player()->SetClass("fighter");
    this_player()->setenv("TITLE", "$N the page");
    this_player()->init_skills("fighter");
    this_player()->setenv("start", "/domains/Praxis/fighter_hall");
    return 1;
}

int go_up() {
    if(this_player()->query_class() != "fighter") {
        write("你无法穿透阻挡通道的力场。");
        say(this_player()->query_cap_name()+"试图进入战士圣地，但失败了。", this_player());
        return 0;
    }
    return 1;
}

