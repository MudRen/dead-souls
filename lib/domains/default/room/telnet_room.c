#include <lib.h>
#include <daemons.h>
#include ROOMS_H

inherit LIB_ROOM;

string LoadIP(){
    if(INTERMUD_D->GetMudList()["Dead Souls Dev"]){
        return INTERMUD_D->GetMudList()["Dead Souls Dev"][1];
    }
    else return "127.0.0.1";
}

string LoadPort(){
    if(INTERMUD_D->GetMudList()["Dead Souls Dev"]){
        return INTERMUD_D->GetMudList()["Dead Souls Dev"][2];
    }
    else return ""+query_host_port();
}

void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("telnet房间");
    SetLong("从这个房间，你可以尝试连接到Dead Souls Dev。如果你需要提问但跨MUD连接中断时，这很有用。注意，处于字符模式会干扰输入。\n\t如果连接失败，请发送邮件到cratylus@comcast.net寻求帮助。一旦连接到Dead Souls Dev，输入\"dcon\"返回你自己的MUD。\n\n输入\"connect\"进行连接\n创造者大厅附属区在西边。");
    SetExits( ([ 
                "west" : "/domains/default/room/wiz_hall2",
                ]) );
    SetNoModify(1);
}

void init(){
    object ding;
    ::init();
    if(!present("telnet_room_client",this_player())){
        ding=new("/secure/obj/tc");
        ding->eventMove(this_player());
        ding->SetConnection(LoadIP()+" "+LoadPort());
    }
}

int CanRelease(object ob){
    if(present("telnet_room_client",ob)){
        present("telnet_room_client",ob)->eventDestruct();
    }
    return 1;
}

int CanReceive(object ob) {
    if(interactive(ob)){
        tell_object(this_object(),ob->GetName()+" is about to enter the telnet room.");
    }
    return 1;
}
