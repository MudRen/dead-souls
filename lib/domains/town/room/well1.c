#include <lib.h>
inherit LIB_ROOM;
int humidity = 0;

string GetDryDesc(){
    string ret = "这是旧镇水井的底部。这里相当黑暗"+
        "且令人不愉快。多年的废弃为"+
        "害虫、泥土和灰尘提供了避风港。某种维修门安装在"+
        "西墙上。\n%^GREEN%^墙上安装着一个拉杆。"+
        "%^RESET%^";
    return ret;
}

string GetWetDesc(){
    string ret = "这是旧镇水井的底部。这里相当黑暗"+
        "且潮湿。某种维修门安装在"+
        "西墙上。\n%^GREEN%^墙上安装着一个拉杆。"+
        "%^RESET%^";
    return ret;
}

string GetWellDesc(){
    string ret;
    if(humidity) ret = GetWetDesc();
    else ret = GetDryDesc();
    return ret;
}

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("镇水井");
    SetLong( (: GetWellDesc :) );
    SetItems( ([
                ({ "bottom","well" }) : "肮脏、发霉且令人不愉快。",
                "haven" : "害虫的好地方。",
                ({"dirt","dust"}) : "这里有很多灰尘。空井很少会在清洁日得到优先考虑。",
                ({"vermin","rats","bugs"}) : "看起来他们此刻正在躲着你。"
                ]) );
    SetInventory(([
                "/domains/town/obj/well_lever" : 1,
                ]));
    SetExits( ([ 
                "up" : "/domains/town/room/south_road1",
                "west" : "/domains/town/room/well2",
                ]) );
    SetDoor("west", "/domains/town/doors/welldoor1.c");
    SetFlowLimit(1);
}

void init(){
    ::init();
}

int eventCompleteQuest(object ob){
    string *quests;
    quests = ob->GetQuests();
    if(ob && !ob->GetQuest("Town Well Quest")){
        ob->AddQuest("the Plumber","Town Well Quest");
        tell_player(ob, "%^BOLD%^%^RED%^You have solved the Town Well Quest.");
        tell_player(ob, "%^BOLD%^%^RED%^Congratulations!");
        tell_player(ob, "%^BOLD%^%^RED%^You are awarded 7 quest points and "+
                "1500 experience points.");
        ob->AddQuestPoints(7);
        ob->AddExperiencePoints(1500);
    }
    return 1;
}

int eventReceiveObject(object ob){
    if(base_name(ob) == LIB_FLOW && !humidity){
        object player;
        mixed wheel = objects((: base_name($1) ==
                    "/domains/town/obj/waterwheel" && clonep($1) :));
        if(sizeof(wheel)) wheel = wheel[0];
        if(objectp(wheel)) player = wheel->GetTurner();
        if(player) eventCompleteQuest(player);
        humidity = 1;
        SetItems(([]));
    }
    return ::eventReceiveObject(ob);
}
