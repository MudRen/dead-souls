#include <lib.h>
inherit LIB_ROOM;

int doorcounter,callfloor,closed,floor,my_counter,moving;
string floorname;
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("教堂电梯");
    SetLong("这是村庄教堂里的电梯。电梯门在东墙上。两个按钮嵌在门旁边的墙上，标有'1'和'b'。");
    floor=1;
    moving = 0;
    closed=1;
    callfloor=0;
    SetExits( ([
                "east" : "/domains/town/room/church",
                ]) );
    SetItems(([
                //new("/domains/town/obj/ebutton1") : 1,
                //new("/domains/town/obj/ebutton2") : 1,
                "elevator" : "一种垂直室内交通工具。","
                "wall" : "按钮在墙上。","
                ({"elevator door","door"}) : "通往外面的门。","
                ]) );
    AddItem(new("/domains/town/obj/ebutton2"));
    AddItem(new("/domains/town/obj/ebutton1"));
    set_heart_beat(1);
}
void init(){
    ::init();
    set_heart_beat(1);
}
int CallMe(int i){
    if(i == floor && moving == 0) {
        this_object()->SetDoorClosed(0);
        return 1;
    }
    else callfloor = i;
    return 1;
}
int SetDoorClosed(int i){
    if(i && i == closed) return i;
    if(!i && closed == 0) return i;
    if(i == 0 && closed == 0) return i;
    if(i) closed = i;
    else if( closed == 1 ) closed = 0;
    else if( closed == 0 ) closed =1;
    if(floor == 1) floorname = "/domains/town/room/church";
    if(floor == 2) floorname = "/domains/town/room/basement";
    if(closed < 1){
        tell_room(this_object(),"电梯门打开了。");
        tell_room(load_object(floorname),"电梯门打开了。");
        doorcounter = 10;
    }
    if(closed > 0) {
        tell_room(this_object(),"电梯门关闭了。");
        tell_room(load_object(floorname),"电梯门关闭了。");
        doorcounter = 0;
    }
    return closed;
}
int SetFloor(int i){
    if(floor == i) return 0;
    RemoveExit("east");
    floor = i;
    if(i == 1) AddExit("east", "/domains/town/room/church");
    if(i == 2) AddExit("east", "/domains/town/room/basement");
    return 1;
}
int CanReceive(object ob) {
#if 1
    if(living(ob) && closed > 0 && query_verb() != "goto" &&
            query_verb() != "trans"  ){
        message("info","电梯门是关闭的。", ob);
        return 0;
    }
#endif
    return 1;
}
int CanRelease(object ob){
    if(archp(ob)) {
        tell_object(ob,"%^RED%^作为大法师，你被允许随时"
                "离开电梯。普通创建者和"
                "玩家不能这样做。%^RESET%^\n");
    }
    if(closed > 0 && query_verb() == "go" ){
        message("info","电梯门是关闭的。", ob);
        return 0;
    }
    return 1;
}
varargs int eventRoll(int i){
    if(!i) i = 10;
    moving = 1;
    SetDoorClosed(1);
    my_counter = i;
    return i;
}
void heart_beat(){
    if(doorcounter > 0){
        doorcounter--;
        if(doorcounter  < 2) SetDoorClosed(1);
    }

    if(moving == 0 && closed == 1 && callfloor > 0){
        tell_room(this_object(),"电梯突然开始移动。");
        eventRoll();
    }

    if(moving && moving > 0){
        my_counter--;
        if(my_counter % 5  == 0) {
            tell_room(this_object(),"电梯继续运行...");
        }

        if(my_counter < 2) {
            my_counter = 0;
            moving = 0;
            SetFloor(callfloor);
            tell_room(this_object(),"电梯到达了目的地。");
            SetDoorClosed(0);
            callfloor = 0;
        }
    }
}
