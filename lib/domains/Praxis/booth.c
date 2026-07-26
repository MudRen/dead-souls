//     /d/standard/booth.c
//     from the Nightmare mudlib
//     a nice, simple polling booth
//     created by Gregon@Nightmare Jan 1994

#include <daemons.h>
#define BOOTH_VOTES "/domains/Praxis/data/booth_votes"
#define BOOTH_QUESTION "/domains/Praxis/data/booth_question"
inherit "/lib/std/room";

int a,b;
mapping vote;

void create() {
    ::create();
    SetShort("噩梦世界公投室");
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetLong(
            "这是噩梦世界的公投室。玩家们来这里对巫师们希望获得意见的"
            "议题进行投票。当前的投票问题张贴在墙上，<read question> 将显示它。"
           );

    SetExits( (["down" : "/domains/Praxis/adv_main"]) );
    vote=([]);
    RestoreObject(BOOTH_VOTES);
}

void init() {
    ::init();
    add_action("vote", "vote");
    add_action("read", "read");
    if(archp(this_player())) add_action("check", "check");

}

int vote(string str) {
    string me;

    me=this_player()->query_name();
    if(str!="a" && str!="b") {
        notify_fail("你只能投票给a或b。\n");
        return 0;
    }
    if(PLAYERS_D->non_voter(me)) {
        write("你被列为第二角色。你不能投票。");
        return 1;
    }
    if(vote[me]) {
        write("你已经投过票了。");
        return 1;
    }
    if(str=="a") {
        vote[me]="a";
        a++;
        write("投票已计数。谢谢。");
        SaveObject(BOOTH_VOTES);
        return 1;
    }
    if(str=="b") {
        vote[me]="b";
        b++;
        write("投票已计数。谢谢。");
        SaveObject(BOOTH_VOTES);
        return 1;
    }

}

int read(string str) {
    if(!str || str != "question") return 0;
    write("当前的投票问题是：\n");
    this_player()->more(BOOTH_QUESTION); 
    return 1;
}

int check(){
    write("A: "+a+"\nB: "+b);
    return 1;
}
