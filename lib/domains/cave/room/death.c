#include <lib.h>
#include <dirs.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

string FunkyPic();
int CheckChat();
int StartHeart(object ob);

protected void create() {
    ::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("脱离凡尘");
    SetLong( (:FunkyPic:) );
    SetObviousExits("no exit");
    set_heart_beat(10);
    SetNoModify(1);
}

void init(){
    ::init();
    add_action("regenerate","regenerate");
    add_action("wander","wander");
    this_object()->CheckChat();
}

string FunkyPic(){
    return "你已经死了！！！";
}

int regenerate(){
    write("伴随着一股巨大的物质和能量洪流，你重新物质化为实体状态，发现自己身处一个熟悉的地方……");
    this_player()->eventRevive();
    this_player()->eventMoveLiving(ROOM_START);
    return 1;
}

int wander(){
    write("你周围传来一种奇怪的、空洞的震动，你意识到某种力量正在迫使你的灵魂前往他处……你发现自己身处一个你熟悉却又奇特崭新的地方。");
    this_player()->eventMoveLiving(ROOM_START);
    return 1;
}

void heart_beat(){
    tell_room(this_object(), "一个声音低语道：\"你可以选择在这里重生为一个新的身体。\"");
    return;
}


int CanRelease(object ob){
    if(userp(ob) && ob->GetGhost() && environment(ob) == this_object()) {
        tell_player(ob,"\n%^RED%^你的亡灵被召回，当你离开冥界时，一个新的身体在你周围重新生成。你又活了！%^RESET%^\n");
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

