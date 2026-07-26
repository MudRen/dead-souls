#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

string LongDesc(){
    string desc = "不朽者们来这里参观他们正在建造的世界的各个部分。创造者大厅在楼上。要访问Dead Souls测试和开发MUD，请向西走。";
    return desc;
}

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("领域房间");
    SetLong("这个房间提供了方便的入口，可以前往各个领域的起始房间和特色区域。");
    SetItems(([
                "Ylsrim" : "这是Ylsrim领域的入口。",
                "campus" : "这是校园领域的入口。",
                "examples" : "这是示例领域的入口。",
                "town" : "这是城镇领域的入口。",
                "cave" : "这是洞穴领域的入口。",
                "praxis" : "这是Praxis领域的入口。",
                "learning" : "这是教程的入口",
                ({ "sign" }) : "一个你可以阅读的指示牌。",
                ]));
    SetEnters( ([
                "campus" : "/domains/campus/room/start",
                "ylsrim" : "/domains/Ylsrim/room/bazaar",
                "examples" : "/domains/examples/room/start.c",
                "cave" : "/domains/cave/room/start",
                "town" : "/domains/town/room/start",
                "learning" : "/domains/learning/room/start",
                "praxis" : "/domains/Praxis/square",
                ]) );
    SetProperty("no attack", 1);
    SetProperty("nopeer",1);
    SetExits(([
                "north" : "/domains/default/room/wiz_hall2",
                ]));

    SetInventory(([
                ]));

    SetRead("sign", (: load_object(ROOM_ARCH)->SignRead() :) );
}

int CanReceive(object ob) {
    if(playerp(ob) && !creatorp(ob) && !present("testchar badge",ob) &&
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
