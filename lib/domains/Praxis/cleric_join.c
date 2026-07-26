#include <lib.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("become", "become");
    add_action("go_north","go");
    add_action("preview","preview");
}

void create() {
    ::create();
    SetProperties( (["light": 2, "indoors" : 1, "no castle" : 1]) );
    SetShort( "普拉克西斯牧师教堂");
    SetLong(
            "你在普拉克西斯的小牧师教堂里。这是一座非常简洁"
            "yet elegant building. The lack of adornment is made up "
            "for in the strong faith you can feel radiating from this little "
            "church. People of all faiths come here for prayer, or solitude. "
            "The clerics initiate young adventurers here into the class of "
            "clerics. <preview> will tell you about becoming a cleric.  "
            "There is a passage north.");
    SetItems(
            (["church" : "西边有一个举行婚礼的小教堂，北边是牧师的内殿。",
             "chapel" : "教堂的牧师在那里举行婚礼。",
             "light" : "一道%^BLUE%^蓝色%^RESET%^光芒保护着这个地方。",
             "passage" : "向北通往牧师的内殿。"]) );
    SetExits(
            (["east" : "/domains/Praxis/n_centre1"]) );
}

int preview() {
    if(this_player()->query_class() != "explorer") {
        message("info", "这不适合你。", this_player());
        return 1;
    }
    message("info", this_player()->query_cap_name()+"想要了解牧师。", this_object(), ({ this_player() }));
    message("info", "欢迎，探索者！", this_player());
    message("info", "牧师是信仰深厚的人，信仰各异，"
            "yet united in their belief in the sanctity of the natural world.  Their "
            "ability to get in touch with the unity of nature through prayer "
            "gives them great healing powers as well as powers of protection.  "
            "Destruction is the most horrible of evils to them, and they will "
            "lose the powers they have through prayer if they become too "
            "destructive.  Type <become cleric> to become a cleric.", this_player());
    return 1;
}

int become(string str) {
    if(!str) {
        notify_fail("成为什么？\n");
        return 0;
    }
    if(str != "cleric") {
        notify_fail("你不能在这里成为那个。\n");
        return 0;
    }
    if(this_player()->query_class() != "explorer") {
        write("你太老了，现在不能开始学习我们的方式！");
        return 1;
    }
    write("牧师高阶女祭司将你引入牧师职业。");
    say(this_player()->query_cap_name()+"成为了一名牧师。", this_player());
    this_player()->SetClass("cleric");
    this_player()->setenv("TITLE", "$N the novice cleric");
    this_player()->init_skills("cleric");
    this_player()->setenv("start", "/domains/Praxis/cleric_hall");
    return 1;
}

int go_north(string str) {
    if(str !="north") return notify_fail("什么？\n");
    if(this_player()->query_class() != "cleric") {
        write("你无法穿透阻挡通道的力场。");
        say(this_player()->query_cap_name()+"试图进入教堂内殿，但失败了。", this_player());
        return 1;
    }
    this_player()->eventMoveLiving("/domains/Praxis/cleric_hall", "through the light in the passage");
    return 1;
}
