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
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "树里面");
    SetLong(
            "树的内部不可思议地占据了比其物理尺寸更大的空间！"
            "火炬环绕着树的木质墙壁，赋予它魔法般的光芒。"
            "一段楼梯向下通往地面上一个被魔法%^BLUE%^蓝色%^RESET%^"
            "光芒保护的洞。高阶法师术士在这里等候，将有抱负的"
            "魔法使用者引入噩梦法师的神秘职业。"
            "<preview>将告诉你如何成为法师。");
    SetItems(
            (["tree" : "像神秘博士的塔迪斯，里面比外面大。",
             "hole" : "洞口通往地下的房间。",
             "light" : "你确信那是一个只允许法师通过的力场。",
             "walls" : "它们由这棵老树的木材制成。一个开口通往外面。",
             "stairs" : "它们非常漂亮。",
             "torch" : "它被魔法锁定在墙上。",
             "warlock" : "他等待着引导新法师。",
             "mage" : "他等待着引导新法师并解释及物动词和不及物动词的区别。",
             "opening" : "通往西大道。",
             "torches" : "它们为房间营造出一种诡异的光芒。"]) );
    SetExits( 
            (["out" :	"/domains/Praxis/west_road3"]) );
    AddExit("down", "/domains/Praxis/mage_hall.c", (:go_down:));
}

int preview() {
    if(this_player()->query_class() != "explorer") {
        message("info", "这不适合你。", this_player());
        return 1;
    }
    message("other_action", this_player()->query_cap_name()+"想要了解法师。", this_object(), ({this_player()}));
    message("info", "欢迎，探索者！", this_player());
    message("info", "法师没有统一的信仰将他们团结在一起，而是因对魔法艺术的热爱而团结。"
            "他们中的一些人是白魔法的虔诚实践者，而另一些则是邪恶的黑法师。"
            "他们的魔法艺术围绕着那些最能帮助他们在物质世界中前进的艺术，"
            "即召唤和魔法战斗的艺术。你可以输入 <become mage> 来加入法师职业。", this_player());
    return 1;
}

int become(string str) {
    if(!str) {
        notify_fail("成为什么？\n");
        return 0;
    }
    if(str != "mage") {
        notify_fail("你不能在这里成为那个。\n");
        return 0;
    }
    if(this_player()->query_class() != "explorer") {
        message("my_action", "你太老了，现在不能开始学习我们的方式！", this_player());
        return 1;
    }
    message("my_action", "高阶法师术士将你引入法师职业。", this_player());
    message("other_action", this_player()->query_cap_name()+"成为了一名法师。", this_object(), ({this_player()}));
    this_player()->SetClass("mage");
    this_player()->setenv("TITLE", "$N the novice mage");
    this_player()->init_skills("mage");
    this_player()->setenv("start", "/domains/Praxis/mage_hall");
    return 1;
}

int go_down() {
    if(this_player()->query_class() != "mage") {
        message("my_action", "你无法穿透阻挡通道的力场。", this_player());
        message("other_action", this_player()->query_cap_name()+"试图进入法师圣地，但失败了。", this_object(), ({this_player() }));
        return 0;
    }
    return 1;
}

