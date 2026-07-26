inherit "/lib/std/room";

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "计划室");
    SetLong( (: this_object(), "go_away" :));
    SetExits( 
            (["west" : "/domains/Praxis/adv_inner",
             ]) );
    AddExit("up", "/domains/Praxis/arch", (:"do_check":));
    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "planning board" }) );
    ob->set_board_id("planning");
    ob->set_max_posts(30);
    ob->move("/domains/Praxis/planning_room");
    ob->SetShort( "规划我们的世界布告板");
    ob->SetLong( "一个用于发布想法以防止他人使用的布告板。\n");
}

int do_check() { return archp(this_player()); }

string go_away() {
    string str;

    if(archp(this_player())) str = "大法师会议室在楼上。";
    else str = "";
    str += "所有想法在出现在这里之前都是无主的。"
        "如果你的想法被采用了，而你没有发布它，那只能怪你自己。";
    return str;
}
void init(){
    ::init();
}
