#include <lib.h>
int go_down();

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("become", "become");
    add_action("preview","preview");
}

void create() {
    ::create();
    SetProperties( (["no castle":1,"light":2,"indoors":1,"no castle":1]));
    SetShort( "卡塔安洞穴");
    SetLong(
            "你在普拉克西斯北边的一个黑暗地下洞穴里。"
            "洞穴墙壁上雕刻着深邃复杂的壁画和符号。"
            "洞穴深处有一条被闪烁的%^BLUE%^蓝色%^RESET%^光芒守护的通道。"
            "<preview>将告诉你如何成为卡塔安。");
    SetItems(
            (["mural" : "它非常古老，描绘了可怕的邪教仪式。",
             "murals" : "它们相当古老，由描绘奇异仪式的图画组成。",
             "light" : "你确信那是一个只允许卡塔安通过的力场。",
             "cavern" : "洞穴几乎因隐藏的邪恶而脉动。"]) );
    SetExits( 
            (["up" : "/domains/Praxis/forest3"]) );
    AddExit("down","/domains/Praxis/kataan_hall",(:go_down:));
}

int preview() {
    if(this_player()->query_class() != "explorer") {
        write("这不适合你。");
        return 1;
    }
    say(this_player()->query_cap_name()+"想要了解卡塔安。", this_player());
    write("欢迎，探索者！");
    write("卡塔安是一个古老的邪恶巫术战士团体，擅长使用投射武器和潜行。"
            "他们小心翼翼地不做任何可能被认为是善行的事情。"
            "相反，他们利用恶魔主人赋予他们的力量来恐吓善良的存在。\n"
            "要成为卡塔安，输入 <become kataan>\n");
    return 1;
}

int become(string str) {
    if(!str) {
        notify_fail("成为什么？\n");
        return 0;
    }
    if(str != "kataan") {
        notify_fail("你不能在这里成为那个。\n");
        return 0;
    }
    if(this_player()->query_class() != "explorer") {
        write("你太老了，现在不能开始学习我们的方式！");
        return 1;
    }
    write("卡塔安大师将你引入卡塔安职业。");
    say(this_player()->query_cap_name()+"成为了一名卡塔安。", this_player());
    this_player()->SetClass("kataan");
    this_player()->setenv("TITLE", "$N the pebble tosser");
    this_player()->init_skills("kataan");
    this_player()->setenv("start", "/domains/Praxis/kataan_hall");
    return 1;
}

int go_down() {
    if(this_player()->query_class() != "kataan") {
        write("你无法穿透阻挡通道的力场。");
        say(this_player()->query_cap_name()+"试图进入卡塔安圣地，但失败了。", this_player());
        return 0;
    }
    return 1;
}


