#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int tutorial = 0;

string DoDesc(){
    string desc = "欢迎！输入以下指令进入主区域：%^%^GREEN%^%^enter town%^%^RESET%^%^\n\n";
    string desc2 = "输入以下指令进入教程区域：%^%^RED%^%^enter tutorial\n\n%^%^RESET%^%^";
    return desc + ( tutorial ? desc2 : "");
}

void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("起始房间");
    SetLong( DoDesc() );
    SetExits( ([
                "south" : "/domains/default/room/wiz_hall",
                ]) );
    SetNoModify(1);
    SetCoordinates("5000,5000,0");
    SetItems( ([
                "tutorial" : "一组让你熟悉这个环境的房间。",
                "town" : "主城镇。",
                ]) );
    SetEnters( ([
                //"tutorial" : "/domains/tutorial/room/start",
                "town" : "/domains/town/room/start",
                ]) );
    if(tutorial){
        AddEnter("tutorial", "/domains/tutorial/room/start");
    }
}

void init(){
    ::init();
}
