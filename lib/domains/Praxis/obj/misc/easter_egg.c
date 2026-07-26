#include <lib.h>

inherit LIB_MEAL;

void create() {
    ::create();
    SetKeyName("easter egg");
    SetId( ({ "egg", "easter egg" }) );
    SetShort("an %^RED%^e%^GREEN%^a%^YELLOW%^s%^BLUE%^t%^MAGENTA%^e"
            "%^CYAN%^r%^RESET%^ egg");
    SetLong(
            "一个由复活节兔子带来的美丽复活节彩蛋。看起来很好吃。"
            "如果你不想吃它，为什么不把它藏起来留给别人呢？"
           );
    SetValue(0);
    SetMass(10);
    if(random(100) < 30) {
        SetStrength(-10);
        SetMealMessages("$N吃了$O，它是臭的！",
                "$N吃了$O，它是臭的！");
    }
    else {
        SetStrength(10);
        SetMealMessages("$N吃了$O，里面装满了美味的糖果！",
                "$N吃了$O，里面装满了美味的糖果！");
    }
}

void init() {
    ::init();
    add_action("cmd_search", "search");
    add_action("cmd_hide", "hide");
}

int cmd_hide(string str) {
    if(present(str, this_player()) != this_object()) return 0;
    message("my_action", "你藏起了"+GetShort()+"。", this_player());
    message("other_action", this_player()->query_cap_name()+
            "藏起了什么东西。", environment(this_player()), ({this_player()}));
    SetInvis(1);
    eventMove(environment(this_player()));
    return 1;
}

int cmd_search(string str) {
    if(!query_invis()) return 0;
    message("my_action", "你找到了"+GetShort()+"！", this_player());
    message("other_action", this_player()->query_cap_name()+
            "找到了"+GetShort()+"！", environment(this_player()),
            ({ this_player() }));
    SetInvis(0);
    return 1;
}
