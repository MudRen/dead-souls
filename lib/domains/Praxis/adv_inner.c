#include <lib.h>

inherit LIB_ROOM;

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "不朽者大厅");
    SetLong(
            "这是噩梦世界不朽者的%^GREEN%^绿色%^RESET%^会议室。"
            "在这个房间里，所有噩梦不朽者讨论泥潭政策和活动事务，"
            "以便每个人都能了解正在发生的事情。南边有一间讨论LPC的房间，"
            "东边有一间计划室，不朽者们在那里发布他们对区域、"
            "领域、公会和任务的计划。下面是审批室。");
    SetExits( 
            (["up" : "/domains/Praxis/mudlib",
             "north" : "/domains/Praxis/adv_main",
             "south" : "/domains/Praxis/lpc_inner",
             "down": __DIR__ "app_room",
             "east" : "/domains/Praxis/planning_room"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "reality board" }) );
    ob->set_board_id("immortal");
    ob->set_max_posts(30);
    ob->move("/domains/Praxis/adv_inner");
    ob->SetShort( "不朽者布告板");
    ob->SetLong( "发布任何不适合在玩家公共论坛上讨论的"
            "关于泥潭的笔记，供不朽者讨论。\n");
    SetProperty("no steal", 1);
}

int CanReceive(object ob) {
    if(!living(ob)) return 1;
    if(!userp(ob)) return 0;
    if(!creatorp(ob)) {
        message("my_action", "你无法穿透蓝色护盾的魔力。", this_player());
        message("other_action", sprintf("%s试图穿过魔法蓝色护盾，但失败了。", this_player()->query_cap_name()),
                environment(this_player()), ({ this_player() }));
        return 0;
    }
    return ::CanReceive(ob);
}
void init(){
    ::init();
}
