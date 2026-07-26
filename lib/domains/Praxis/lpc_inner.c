inherit "/lib/std/room";

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "LPC和MudOS室");
    SetLong(
            "不朽者们来这里讨论编码问题。"
            "不朽者大厅在北边。");
    SetExits( 
            (["north" : "/domains/Praxis/adv_inner"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "irreality board" }) );
    ob->set_board_id("coding");
    ob->set_max_posts(20);
    ob->move("/domains/Praxis/lpc_inner");
    ob->SetShort( "LPC和MudOS非现实布告板");
    ob->SetLong( "在这里发布你的编码问题。\n");
}
void init(){
    ::init();
}
