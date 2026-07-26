//    project_room.c
//    Nightmare Mudlib
//    The Project Room
//    by Kalinash@Nightmare on June 30, 1994.

#include <lib.h>
#include <daemons.h>

inherit LIB_ROOM;

void init() {
    ::init();
    add_action("start_fun", "start");
    add_action("list_fun", "list");
}

void create() {
    ::create();
    SetProperties( ([
                "light" : 2, 
                "no kill" : 1,
                "no steal" : 1,
                "no magic" : 1,
                "no teleport" : 1,
                "no castle" : 1
                ]) );
    SetShort("项目室");
    SetLong("欢迎来到项目追踪部门！\n"
            "墙上印着一份命令列表，使用 <read list> 查看。"
            "你可以来这里了解噩梦世界不朽层面正在发生的事情。");
    SetExits( ([ "west" : "/domains/Praxis/mudlib" ]) );
}

int start_fun(string group) {
    if(!group) {
        message("my_action", "开始什么？", this_player());
        return 1;
    }
    //if(!PROJECT_D->add_group(group, this_player()->query_name()))
    //   return notify_fail("Error in the daemon.\n");
    //message("my_action", sprintf("Group '%s' successfully created.",
    // group), this_player());
    return 1;
}

int list_fun(string which) {
    if(!which)
        return notify_fail("列出什么？\n");
    if(which == "groups")
        return;
}
