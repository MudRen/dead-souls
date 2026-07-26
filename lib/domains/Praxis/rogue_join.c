inherit "/lib/std/room";
int go_down();

void init() {
    ::init();
    add_action("become", "become");
    add_action("preview","preview");
}

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("indoors", 1);
    SetShort( "盗贼小屋");
    SetLong(
            "你偶然发现了噩梦盗贼的藏身处。"
            "外表看起来像一间破旧的小屋，里面实际上是一座精心建造的堡垒。"
            "一道魔法%^BLUE%^蓝色%^RESET%^光芒"
            "守护着通往堡垒核心的楼梯入口。"
            "盗贼大师在这里等候，将新的渣滓引入邪恶卑鄙的盗贼职业。"
            "<preview>将告诉你如何成为盗贼。");
    SetItems(
            (["hideout" : "盗贼们来这里策划邪恶行为。",
             "shack" : "它不是真正的小屋，而是一座堡垒。",
             "fortress" : "盗贼们把这里当作藏身处。",
             "light" : "只有盗贼才能通过。",
             "stairs" : "它们通往盗贼藏身处的核心。",
             ({"rogue", "master", "grand master rogue"}) : "他引导"
             "新的盗贼。"]) );
    SetExits( ([
                "west" : "/domains/Praxis/rain_forest.c",
                ]) );
    AddExit("down","/domains/Praxis/rogue_hall",(:go_down:));
}

int preview() {
    if(this_player()->query_class() != "explorer") {
        write("这不适合你。");
        return 1;
    }
    say(this_player()->query_cap_name()+"想要了解盗贼。", this_player());
    write("欢迎，探索者！\n");
    write("盗贼是以他人的痛苦为生和取乐的人。"
            "他们把藏身处设在外域，以便在只对他们"
            "感兴趣、想把他们绳之以法的文明世界面前保持低调。"
            "盗贼由许多不同类型的渣滓组成。有些是杀人犯，"
            "有些是小偷和强盗。但他们都很享受。"
            "请记住，一旦你选择成为盗贼，你将被"
            "各行各业的人所憎恨。你将永远无法安全地行动。"
            "除非你避免以玩家为目标。"
            "输入 <become rogue> 成为盗贼。");
    return 1;
}

int become(string str) {
    if(!str) {
        notify_fail("成为什么？\n");
        return 0;
    }
    if(str != "rogue") {
        notify_fail("你不能在这里成为那个。\n");
        return 0;
    }
    if(this_player()->query_class() != "explorer") {
        write("你太老了，现在不能开始学习我们的方式！");
        return 1;
    }
    write("盗贼大师将你引入盗贼职业。");
    say(this_player()->query_cap_name()+"成为了一名盗贼。", this_player());
    this_player()->SetClass("rogue");
    this_player()->setenv("TITLE", "$N the novice rogue");
    this_player()->init_skills("rogue");
    this_player()->setenv("start", "/domains/Praxis/rogue_hall");
    return 1;
}

int go_down() {
    if(this_player()->query_class() != "rogue") {
        write("你无法穿透阻挡通道的力场。");
        say(this_player()->query_cap_name()+"试图进入堡垒核心，但失败了。", this_player());
        return 0;
    }
    return 1;
}
