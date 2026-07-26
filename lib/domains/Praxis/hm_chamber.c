//High Mortal Meeting Room written by Lassondra of Sunshine
//with help from that Borg geek 5/8/94
inherit "/lib/std/room";

int CanReceive(object ob) {
    if(!userp(ob) || high_mortalp(ob) || creatorp (ob)) return 1;
    write( "你不能进去！");
    return 0;
}

void init() {
    ::init();
    add_action( "sit", "sit" );
}

void create(){
    object ob;
    ::create();
    SetProperties( ([ "light" : 3, "no steal" : 1, "no magic" : 1,
                "no teleport" : 1, "no attack" : 1, "no castle" : 1, "no bump" : 1 ]) ); 
    SetShort( "高级凡人密室" );
    SetLong( "你进入了噩梦世界高级凡人的论坛。你看到一张大圆桌立在房间中央，"
            "周围环绕着橡木椅。%^BLUE%^蓝色%^RESET%^地毯铺在地上，"
            "墙壁被漆成了奶油色。"
           );
    SetItems( ([
                "table" : "一张大型圆形橡木桌。",
                "chairs" : "椅子与桌子的木材相配。",
                "carpet" : "地毯是深蓝色的。",
                "walls" : "墙壁是奶油色的。"
                ]) );
    SetExits( ([ "east" : "/domains/Praxis/ombud_hall.c" ]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "high mortal board", "bulletin board"}) );
    ob->set_board_id("hm_board");
    ob->set_max_posts(30);
    ob->set_edit_ok( ({"lassondra"}) );
    ob->set_location("/domains/Praxis/hm_chamber");
    ob->SetShort( "高级凡人智慧布告板");
    ob->SetLong( "这是高级凡人的智慧布告板。它"
            "用于高级凡人讨论有关泥潭福利的问题。");
}

int sit(string str) {
    if(!str || str!="chair" ) {
        notify_fail( "坐在哪里？\n");
        return 0;
    }

    write( "你坐在橡木椅上。");
    return 1;
}
