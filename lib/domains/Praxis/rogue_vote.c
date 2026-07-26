#include <lib.h>
#include <voting.h>
#include <daemons.h>

inherit "/domains/town/room/voters";

void create() {
    ::create();
    SetProperty("light", 1);
    SetProperty("no castle", 1);
    SetProperty("indoors", 1);
    SetShort( "盗贼投票厅");
    SetLong( (: this_object(), "new_long" :));
    SetItems(
            (["list" : "在选举期间，它列出所有候选人。"]) );
    SetExits( 
            (["west" : "/domains/Praxis/rogue_hall"]) );
}

string new_long() {
    if(VOTING_D->election_day())
        return "这是盗贼们可以参选的房间。"
            "如果你想参选，只需输入命令"
            "'enter'，你就会被添加到列表中。候选人名单张贴在墙上。";
    else return "这是盗贼大厅的投票室。"
        "盗贼们将在这里聚集参加下一次选举："+VOTING_D->query_vote_date()+"。";
}
void init(){
    ::init();
}
