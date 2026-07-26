#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;
int ds;

protected void create() {
    object ob;
    room::create();
    if(mud_name() == "Dead Souls"){
        ds = 1;
    }
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("创造者大厅楼上");
    SetLong("这是创造者大厅的楼上附属区。东边是telnet房间，你可以连接到Dead Souls测试和开发MUD。南边是领域房间，你可以方便地访问各个特色领域或区域。主大厅在楼下。");
    SetProperty("no attack", 1);
    SetProperty("nopeer",1);
    ob = new("/lib/bboard");
    ob->SetKeyName("chalkboard");
    ob->SetId( ({ "board", "chalkboard", "dusty board", "dusty chalkboard" }) );
    ob->set_board_id("immortal_board");
    ob->set_max_posts(30);
    SetShort("创造者大厅西翼");
    ob->eventMove(this_object());
    SetItems( ([
                ({"sign"}) : "一个你可以阅读的指示牌。",
                ]) );
    SetExits( ([
                "south" : "/domains/default/room/domains_room",
                "down" : "/domains/default/room/wiz_hall",
                "east" : "/domains/default/room/telnet_room.c",
                ]) );
    if(!ds){
    }
    SetInventory(([
                ]));

    SetRead("sign", (: load_object(ROOM_ARCH)->SignRead() :) );
}

int CanReceive(object ob) {
    if(playerp(ob) && !creatorp(ob) &&
            !member_group(ob,"TEST")) {
        message("info","仅限创造者工作人员使用，抱歉。", ob);
        return 0;
    }

    if(ob->GetRace() == "rodent"){
        message("info","你被灭鼠剂驱赶了。",ob);
        return 0;
    }
    return 1;
}
void init(){
    ::init();
}
