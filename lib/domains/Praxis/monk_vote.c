#include <lib.h>
#include <voting.h>
#include <daemons.h>

inherit "/domains/town/room/voters";

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("no castle", 1);
    SetProperty("indoors", 1);
    SetShort( "僧侣投票厅");
    SetLong( (: this_object(), "new_long" :));
    SetItems(
            (["list" : "在选举期间，它列出所有候选人。"]) );
    SetExits( 
            (["west" : "/domains/Praxis/monk_hall"]) );
}

string new_long() {
    if(VOTING_D->election_day())
        return "这是僧侣们可以参选的房间。"
            "如果你想参选，只需输入命令"
            "'enter'，你就会被添加到列表中。候选人名单张贴在墙上。"
            "输入'list candidates'查看名单。";
    else return "这是僧侣大厅的投票室。"
        "僧侣们将在这里聚集参加下一次选举："+VOTING_D->query_vote_date()+"。";
}
void init(){
    ::init();
}
