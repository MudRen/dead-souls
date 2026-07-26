#include <lib.h>
#include <dirs.h>
#include ROOMS_H

inherit LIB_ROOM;

string FunkyPic();
int CheckChat();
int StartHeart(object ob);

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("脱离尘世");
    SetLong( (:FunkyPic:) );
    SetObviousExits("no exit");
    set_heart_beat(10);
    SetNoModify(1);
}

void init(){
    ::init();
    add_action("regenerate","regenerate");
    add_action("regenerate","choose");
    add_action("wander","wander");
    this_object()->CheckChat();
}

string FunkyPic(){
    return "你已经死了！！！";
}

int regenerate(){
    write("伴随着大量物质和能量的涌动，你重新凝聚成实体形态，发现自己身处一个熟悉的地方……");
    this_player()->eventRevive();
    this_player()->eventMoveLiving(ROOM_START);
    return 1;
}

int wander(){
    write("你周围有一种奇怪的、空洞的振动，你意识到某种力量正在驱使你的灵魂前往别处……你发现自己来到了一个你认识的地方，却又莫名地崭新。");
    this_player()->eventMoveLiving(ROOM_START);
    return 1;
}

void heart_beat(){
    tell_room(this_object(), "一个声音低语道："你可以选择在这里重生为新的身体。"");
    return;
}


int CanRelease(object ob){
    if(userp(ob) && ob->GetGhost() && environment(ob) == this_object()) {
        tell_player(ob,"\n%^RED%^你的不死之魂被召回，当你离开冥界时，一个新的身体在你周围重新凝聚。你复活了！%^RESET%^\n");
        ob->eventRevive();
    }
    return 1;
}

int CanReceive(object ob){
    if(!living(ob)){
        return 0;
    }
    return ::CanReceive(ob);
}

