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
    SetLong("这是一座小型建筑，冒险者们可以在此记录他们的冒险经历，并为其他勇敢的灵魂留下消息和公告。这里也是寻求晋升的地方，如果你有资格成为更高级别的冒险者，向公会会长提出请求即可。一份卷轴列出了可以完成的任务，一块告示牌上写着一些说明。创造者大厅在南边，楼上是特殊技能训练区。东边有一间会议室，供人们私下讨论事务。");
    SetItems( ([
                ({ "list","scroll"}) : "一份卷轴挂在墙上，列出了你可以完成的一些冒险任务，完成后可能会获得奖励。",
                ({"sign","instructions"}) : "这块告示牌上写着关于如何获取经验值和获得晋升的一般性说明。",
                ({"building","small building","here"}) : "你正身处冒险者公会之中。",
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
    ob->SetShort("a dusty chalkboard");
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
