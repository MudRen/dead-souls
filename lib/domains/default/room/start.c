#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int tutorial = 0;

string DoDesc(){
    string desc = "欢迎！要进入主要区域，请输入：%^%^GREEN%^%^enter town%^%^RESET%^%^\n\n";
    string desc2 = "要进入教程区域，请输入：%^%^RED%^%^enter tutorial\n\n%^%^RESET%^%^";
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
                "town" : "主要城镇。",
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
