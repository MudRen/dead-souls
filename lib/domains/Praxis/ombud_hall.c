inherit "/lib/std/room";

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetShort( "投诉部");
    SetLong(
            "你在一个黑暗、发霉的房间里。这是噩梦世界官方的"
            "投诉部门。把你希望巫师们解决的任何不满、问题或评论"
            "发布在布告板上。");
    SetExits( 
            ([
             "up" : "/domains/Praxis/adv_main",
             "west" : "/domains/Praxis/hm_chamber.c"
             ]) 
            );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "comments board", "board" }) );
    ob->set_board_id("ombud");
    ob->set_max_posts(50);
    ob->set_edit_ok( ({ "nialson", "ninja" }) );
    ob->SetShort("投诉者布告板");
    ob->SetLong( "这个世界的人们来这里发布他们的评论和问题，"
            "给控制所有现实命运的不朽者们看。\n");
    ob->move(this_object());
    SetProperty("no steal", 1);
    SetProperty("no attack", 1);
    SetProperty("no castle", 1);
}

void init(){
    ::init();
} 
