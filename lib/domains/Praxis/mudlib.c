inherit "/lib/std/room";

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "泥潭库室");
    SetLong(
            "在这个房间里你可以看到泥潭库部门对游戏漏洞的修复状态，"
            "也可以报告那些你认为没有得到应有关注的漏洞。");
    SetExits( 
            (["down" : "/domains/Praxis/adv_inner"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board" }) );
    ob->set_board_id("mudlib");
    ob->set_max_posts(50);
    ob->move("/domains/Praxis/mudlib");
    ob->SetShort( "泥潭库布告板");
    ob->SetLong( "一个用于发布完全无意义内容的布告板。\n");
}
void init(){
    ::init();
}

