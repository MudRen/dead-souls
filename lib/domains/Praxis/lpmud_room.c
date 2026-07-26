#include <lib.h>

inherit LIB_ROOM;

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "LPMud室");
    SetLong(
            "新LPMud的广告张贴在这里。"
            "其他布告板上的广告将被迅速删除。");
    SetExits( 
            (["west" : "/domains/Praxis/adv_main"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "lpmud board" }) );
    ob->set_board_id("lpmud");
    ob->set_max_posts(20);
    ob->move("/domains/Praxis/lpmud_room");
    ob->SetShort( "LPMud广告布告板");
    ob->SetLong( "这个布告板用于推广各地的LPMud。"
            "请随意在这里发布你知道的泥潭信息。\n");
}

void init(){
    ::init();
} 
