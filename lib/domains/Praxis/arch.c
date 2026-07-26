inherit "/lib/std/room";

void init() {
    ::init();
    if(!archp(this_player()))
        this_player()->eventMoveLiving("/domains/Praxis/planning_room", "down");
}

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "大法师室");
    SetLong(
            "这里是大法师们决定噩梦世界命运的地方。");
    SetExits( 
            (["down" : "/domains/Praxis/planning_room"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board" }) );
    ob->set_board_id("arch");
    ob->set_max_posts(20);
    ob->move("/domains/Praxis/arch");
    ob->SetShort( "大法师布告板");
    ob->SetLong( "一个用于发布完全无意义内容的布告板。\n");
}

