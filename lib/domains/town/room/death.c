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
    return read_file("/domains/default/etc/death.txt");
}

int regenerate(){
    write("随着物质和能量的巨大涌动，你重新物质化成一个实体状态，发现自己在一个熟悉的地方...");
    this_player()->eventRevive();
    this_player()->eventMoveLiving(ROOM_START);
    return 1;
}

int wander(){
    write("你周围有一种奇怪而空洞的振动，你意识到某种力量正在将你的空灵形态带往其他地方...你发现自己在一个你所知的地方，却又出奇地新鲜。");
    this_player()->eventMoveLiving(ROOM_START);
    return 1;
}

void heart_beat(){
    tell_room(this_object(), "一个声音低语：\"你可以选择在这里重生成一个新的身体。\"");
    return;
}


int CanRelease(object ob){
    if(userp(ob) && ob->GetGhost() && environment(ob) == this_object()) {
        tell_player(ob,"\n%^RED%^你的亡灵灵魂被召回，当你离开冥界时，一个新的身体在你周围重生。你又活过来了！%^RESET%^\n");
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

