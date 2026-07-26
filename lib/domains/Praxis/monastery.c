#include <lib.h>

inherit LIB_ROOM;

object *begging;

void init() {
    ::init();
    add_action("confess", "confess");
    add_action("pray", "pray");
}

void create() {
    ::create();
    SetListen("default", "你听到楼梯上传来微弱的诵经声。");
    SetListen("upstairs", "你听到僧侣们的诵经声。");
    SetListen("chants", "我们在干旱的季节侍奉一位老人\n"
            "沙漠阳光下的灯塔守护者\n"
            "沉睡者和白色背叛的梦者\n"
            "我们梦想着雨水和枪支的历史\n");
    begging = ({});
    SetShort( "普拉克西斯修道院");
    SetLong(
            "你正身处普拉克西斯华丽的修道院。\n"
            "在这座由普拉克西斯僧侣管理的巨大开放式修道院中，"
            "可悲的杀人犯来此忏悔，死者来此祈祷复活。"
            "东边的小楼梯通往修道院的阁楼和地下室。"
            "僧侣为人们主持婚礼的普拉克西斯教堂在北边。"
            "博克拉路在修道院南边的外面。");
    SetExits( 
            (["south" : "/domains/Praxis/e_boc_la1",
             "east" : "/domains/Praxis/stairs",
             "north" : "/domains/Praxis/chapel"]) );
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetItems(
            (["monastery" : "噩梦僧侣的家园。",
             "chamber" : "人们死后来这里祈祷复活。",
             "stairway" : "通往阁楼和地下室的小型螺旋楼梯。",
             "road" : "博克拉路。"]) );
    SetProperty("no attack", 1);
    SetProperty("no steal", 1);
    SetProperty("no castle", 1);
}

int pray() {
    if(!this_player()->query_ghost()) {
        notify_fail("活人不需要祈祷复活。\n");
        return 0;
    }
    this_player()->revive();
    this_player()->SetHealthPoints(10);
    this_player()->set_heart_beat(1);
    this_player()->set_heal_rate(2);
    return 1;
}

int confess(string str) {
    object *inv;
    int i, ok;
    string res;

    if(str != "murder") {
        notify_fail("忏悔什么？\n");
        return 0;
    }
    ok = 0;
    if(sscanf(this_player()->getenv("TITLE"), "%s murderer $N%*s", res)
            != 1) {
        notify_fail("你不是杀人犯。\n");
        return 0;
    }
    i = sizeof(inv = all_inventory(this_object()));
    while(i--) if(inv[i]->query_class() == "monk") ok = 1;
    if(!ok) {
        write("这里没有人可以让你忏悔。");
        return 1;
    }
    message("my_action", "你恳求僧侣们原谅你杀害了"+lower_case(res)+"。", this_player());
    message("my_action", ("你祈祷宽恕不意味着死亡。"), this_player());
    say(this_player()->query_cap_name()+"为自己杀害了"+
            lower_case(str)+"而恳求宽恕。");
    begging += ({ this_player() });
    call_out("forgive", 60, this_player());
    return 1;
}

object *query_forgiven() { return begging; }

void forgive(object ob) {
    string tmp;

    if(member_array(ob, begging) == -1) return;
    begging -= ({ ob });
    tmp = call_other("/domains/Praxis/"+ob->query_class()+"_hall",
            "get_new_title", ob);
    message("info", "你现在被宽恕了。", ob);
    ob->setenv("TITLE", tmp);
    ob->add_mp(-500);
    ob->add_hp(100- (ob->query_skill("faith")));
}


