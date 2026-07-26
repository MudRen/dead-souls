inherit "/lib/std/room";

void init() {
    ::init();
    //add_action("enter_opening", "enter");
}

void create() {
    ::create();
    SetProperty("light", 2);
    SetShort( "热带荒野");
    SetLong(
            "你在一片沿着东北方向小径变得越来越茂密的丛林中。"
            "小径向西变宽，通往冒险村庄普拉克西斯。"
           );
    SetItems(
            (["jungle" : "一片充满亡命之徒和神秘事物的荒野区域。\n",
             "village" : "冒险者的城镇普拉克西斯。",
             "vegetation" : "向东越来越茂密。",
             "path" : "你可以看到它向西通往村庄。",
             ]) );
    SetSkyDomain("town");
    SetExits( 
            (["northeast" : "/domains/Praxis/jungle",
             "west" : "/domains/Praxis/wild1"]) );
}

int enter_opening(string str) {
    if(!str) {
        notify_fail("进入什么？\n");
        return 0;
    }
    if(str != "opening" && str != "hole" && str != "jungle") {
        notify_fail("这里没有那个可以进入。\n");
        return 0;
    }
    this_player()->eventMoveLiving("/domains/Praxis/outland1", "into the jungle");
    return 1;
}

