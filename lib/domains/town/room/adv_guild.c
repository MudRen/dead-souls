#include <lib.h>
#include <daemons.h>
inherit LIB_ROOM;

object ob;
mapping Levels = PLAYERS_D->GetLevelList();
int ReadSign();
int ReadScroll();

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("冒险者公会");
    SetLong("这座小建筑是冒险者们记录冒险经历并为其他勇敢的灵魂留下消息和公告的地方。这里也是寻求提升等级的地方，如果你应该成为更高级别的冒险者，向公会会长请求即可。一个卷轴列出了可以执行的任务，一个标牌包含了一些说明。创造者的殿堂在南边，楼上有专门的技能训练区域，东边是会议室，人们可以在那里私下讨论。");
    SetItems( ([
                ({ "list","scroll"}) : "一个卷轴挂在墙上，列出了一些你可以执行的冒险任务，这些任务可能会给你带来奖励。",
                ({"sign","instructions"}) : "这个标牌包含了一些关于如何获得经验和提升等级的一般说明。"
                ({"building","small building","here"}) : "你在冒险者公会里。"
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/vill_road2",
                "south" : "/domains/default/room/builder_hall",
                "east" : "/domains/town/room/confroom",
                "up" : "/domains/town/room/training.c",
                ]) );
    SetInventory(([
                "/domains/town/obj/bin" : 1,
                "/domains/town/obj/table" : 1,
                "/domains/town/npc/dirk" : ({60, 1})
                ]));
    SetRead( ([
                ({"list","scroll"}) : (: ReadScroll :),
                ({"instructions","sign"}) : (: ReadSign :)
                ]) );

    SetProperty("no attack", 1);
    ob = new(LIB_BOARD);
    ob->SetKeyName("chalkboard");
    ob->SetId( ({ "board", "chalkboard", "dusty board", "dusty chalkboard" }) );    
    ob->set_board_id("adv_guild_board");
    ob->set_max_posts(30);
    ob->SetShort("一个布满灰尘的写字板");
    ob->eventMove(this_object());
    SetNoClean(1);
}

mixed ReadSign(){
    int i;
    string ret = read_file("/domains/town/txt/advancement.txt");
    ret += "\n";
    for(i=1;i<21;i++){
        ret +=  sprintf("%:-3s     %:-28s %:-12s %:16s\n", i+"",
                Levels[i]["title"], Levels[i]["xp"]+"", (Levels[i]["qp"] || "none")+"");
    }
    ret += "\nTo advance, ask the guildmaster.\nExample:\n\n";
    ret += "ask dirk to advance";
    return this_player()->eventPage(({ret}));
}

mixed ReadScroll(){
    return this_player()->eventPage("/domains/town/txt/quests.txt");
}

void init(){
    ::init();
}
