#include <lib.h>

inherit LIB_ROOM;

string ReadSign(){
    this_player()->more("/domains/town/txt/praxis_sign.txt");
    return "";
}

void create() {
    object borg;

    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 2);
    SetProperty("no steal", 1);
    SetProperty("no magic", 1);
    SetProperty("no attack", 1);
    SetProperty("no castle", 1);
    SetListen("default", "繁忙冒险小镇的各种声音充斥着四周。");
    SetShort( "纪念碑广场");
    SetLong( "你位于纪念碑广场，这里曾被称为克拉斯纳广场。"
            "普瑞克斯的两条主要道路在此交汇，梦魇世界的所有人"
            "在此聚集，分享着喜怒哀乐。南北走向的道路叫做中心大道，"
            "而东西走向的道路则名为博克拉路。"
            "\n%^RED%^这里有一个可以阅读的标牌。%^RESET%^");
    SetExits( 
            (["north" : "/domains/Praxis/n_centre1",
             "south" : "/domains/Praxis/s_centre1",
             "east" : "/domains/Praxis/e_boc_la1",
             "west" : "/domains/Praxis/w_boc_la1"]) );

    //new("/domains/Praxis/obj/misc/watchtower")->move(this_object());
    SetItems(
            (["road" : "博克拉路向东通往冒险者大厅和普瑞克斯修道院。",
             "path" : "中心大道向南通往银行和邮局。",
             "sign" : "一个你可以阅读的标牌。",
             "square" : "克拉斯纳广场是普瑞克斯的中心点。"]) );
    SetInventory(([
                "/domains/Praxis/obj/misc/stargate" : 1,
                ]));
    SetRead("sign", (: ReadSign :) );
    SetCoordinates("1000,-1000,0");
    SetSkyDomain("town");
}

int CanReceive(object ob) { 
    string start;

    if (previous_object()->is_player()) {
        start = previous_object()->getenv("start");
        if (!start) return ::CanReceive(ob);
        if (9>strlen(start)) return ::CanReceive(ob);
        if ("/d/" == start[0..2]) 
            previous_object()->setenv("start", 
                    "/domains/"+start[3..strlen(start)]);
        if ("d/" == start[0..1]) 
            previous_object()->setenv("start", 
                    "/domains/"+start[2..strlen(start)]);
        if ("/wizards/" == start[0..8]) 
            previous_object()->setenv("start", 
                    "/realms/"+start[9..strlen(start)]);
        if ("wizards/" == start[0..7]) 
            previous_object()->setenv("start", 
                    "/realms/"+start[8..strlen(start)]);

        if("/domains/standard/" ==start[0..17])
            previous_object()->set_primary_start("/domains/Praxis/"+
                    start[18..strlen(start)]);
        if("domains/standard/"==start[0..16])
            previous_object()->set_primary_start("/domains/Praxis/"+
                    start[17..strlen(start)]);
    }
    return ::CanReceive(ob);
}
void init(){
    ::init();
}
