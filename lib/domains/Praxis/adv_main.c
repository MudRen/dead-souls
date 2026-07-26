#include <lib.h>

inherit STD_ROOM;

int get_exp(int lev);
int train_player(object tp, string which, int amount);
int get_stat_cost(int x, int lev);

void create() {
    object ob;

    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetNoClean(1);
    SetShort( "冒险者大厅");
    SetLong(
            "这里是普拉克西斯镇的冒险者大厅。它是一座大型木制建筑，"
            "因多年的使用而显得破旧。房间中央立着一块大型布告板，"
            "上面贴满了这个世界的众多冒险者的笔记。"
            "建筑前方，博克拉路向北延伸。南边有一条"
            "被闪烁的%^BLUE%^蓝色%^RESET%^光芒照亮的小通道。");
    SetExits(
            (["north" : "/domains/Praxis/e_boc_la2",
             "east" : "/domains/Praxis/lpmud_room",
             "south" : "/domains/Praxis/adv_inner",
             "down" : "/domains/Praxis/ombud_hall"]) );
    SetItems(
            (["hall" : "一个热闹的地方！",
             "road" : "穿过普拉克西斯的小土路。",
             "passage" : "被%^BLUE%^蓝色%^RESET%^光芒照亮。",
             "light" : "可能是力场。"]) );

    ob = new("/lib/bboard");
    ob->SetKeyName("board");
    ob->SetId( ({ "board", "bulletin board", "reality board" }) );
    ob->set_board_id("main_board");
    ob->SetShort("噩梦世界布告板");
    // ob->SetShort( "The Nightmare Reality Board");
    ob->SetLong( "一块老旧的软木板，经过普拉克西斯的冒险者们"
            "在上面发布他们发现的世界信息。\n");
    ob->set_max_posts(75);

    ob->move(this_object());
    SetProperty("no steal", 1);
    SetProperty("no attack", 1);
}

int go_south() {
    if(!creatorp(this_player())) {
        write("%^BLUE%^%^BOLD%^你无法穿透蓝色光芒的力量。");
        say(this_player()->query_cap_name()+"试图穿过通道，但失败了。", this_player());
        return 0;
    }
    return 1;
}

int get_exp(int lev) {
    int val;

    switch(lev) {
        case 0: val = 0; break;
        case 1: val = 1014; break;
        case 2: val = 2028; break;
        case 3: val = 3056; break;
        case 4: val = 4800; break;
        case 5: val = 6200; break;
        case 6: val = 9100; break;
        case 7: val = 12500; break;
        case 8: val = 15000; break;
        case 9: val = 20000; break;
        case 10: val = 28000; break;
        case 11: val = 40000; break;
        case 12: val = 55000; break;
        case 13: val = 72000; break;
        case 14: val = 104000; break;
        case 15: val = 150000; break;
        default: val = (lev-12)*(lev-15)*28000 + 150000;
    }
    return val;
}

int train_player(object tp, string which, int amount) {
    int exp, amt;

    if(amount < 1) {
        notify_fail("你不能训练那么多。\n");
        return 0;
    }
    exp = tp->query_exp();
    if(exp-amount < get_exp(tp->query_level())) {
        notify_fail("你没有足够的经验值来训练那么多。\n");
        return 0;
    }
    if(tp->query_max_skill(which) <= tp->query_skill(which)) {
        notify_fail("你无法再提升这项技能了。\n");
        return 0;
    }
    amt = ( tp->query_level() * 4 ) + 20;
    if(amt <= tp->query_skill(which) )
    {
        notify_fail("你必须提升等级才能继续训练这项技能。\n");
        return 0;
    }
    tp->add_skill_points(which, amount/4);
    tp->add_exp(-amount);
    tell_object(tp, "你训练了"+which+"技能。");
    return 1;
}

int get_stat_cost(int x, int lev) {
    if(x==1) return ((lev/10)*(lev/10)*10000) + (lev/3)*1000;
    else return (lev/7)*(lev/7)*(lev*900);
}

void init(){
    ::init();
}
