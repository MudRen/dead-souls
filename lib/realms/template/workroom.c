#include <lib.h>
#include ROOMS_H
#include "./area/customdefs.h"

inherit LIB_ROOM;
int ReadSign();
int ReadSheet();
int privacy = 0;
string privs = "";
string LongString(){
    string ret = "你正站在强大的" + privs +
        "的工作间中！\n你可以向下走返回创作者大厅。\n"+
        "示例房间在东边。"+
        "\n%^GREEN%^这里有一块提示牌可以阅读。%^RESET%^"+
        "\n%^GREEN%^这里有一张便条可以阅读。%^RESET%^";
    if(privacy) ret += "\n%^YELLOW%^一个隐私力场 "+
        "正围绕着这个房间激活。%^RESET%^";
    return ret;
}

protected void create() {
    room::create();
    privs = query_privs();
    if( privs ) privs = capitalize(privs);
    else privs = "a creator";

    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort(possessive_noun(privs) + "的工作间");
    SetLong( (: LongString :) );
    SetItems( ([ "workroom" : "看起来很不错。",
                ({"sign","hint","hints"}) : "一块给创作者的提示牌。",
                ({"sheet","reminder","reminders"}) : "一张给创作者的快速提醒便条。",
                ]) );
    SetRead( ([
                ({"sign","hint","hints"}) : (: ReadSign :),
                ({"sheet","reminder","reminders"}) : (: ReadSheet :)
                ]) );
    SetInventory( ([
                MY_OBJ "/chest" : 1,
                "/domains/default/obj/bbucket" :1,
                ]) );
    SetExits( ([ "down" : "/domains/default/room/wiz_hall.c",
                "east" : MY_ROOM "/sample_room"
                ]) );
    SetNoModify(0);
}

int ReadSign(){
    this_player()->eventPage("/news/hints.txt");
    return 1;
}

int ReadSheet(){
    this_player()->eventPage("/news/reminders.txt");
    return 1;
}

void init(){
    ::init();
    add_action("mod_privacy","privacy");
    add_action("mod_privacy","priv");
}

int CanReceive(object sneak) {
    int ret;
    object *living_stack;
    if(!privacy) return ::CanReceive(sneak);
    living_stack = get_livings(sneak);
    if(!living_stack || !arrayp(living_stack)) living_stack = ({ sneak });
    foreach(object ob in living_stack){
        if(!archp(ob) && ob->GetKeyName() != lower_case(privs)){
            message("info","You bounce off the privacy field.", ob);
            message("info",ob->GetName()+" bounced off the privacy field.",
                    this_object());
            if(!environment(ob)) ob->eventMoveLiving(ROOM_START);
            return 0;
        }
    }
    ret = ::CanReceive(sneak);
    if(ret){
        tell_room(this_object(), "\n\nPRIVACY WARNING: "+identify(sneak)+
                " has entered the room.\n\n", sneak);
    }
    return ret;
}

protected int set_privacy(int i){
    object *npcs = filter(deep_inventory(this_object()),
            (: living($1) && !interactive($1) :) );
    privacy=i;
    SetProperty("no peer", i);
    if(sizeof(npcs)){
        foreach(object npc in npcs){
            tell_room(this_object(),"Ejecting "+identify(npc),npc);
            npc->eventMove(ROOM_FURNACE);
        }
    }
    return i;
}

int mod_privacy(string str){
    if(!archp(this_player()) &&
            this_player()->GetKeyName() != lower_case(privs)) {
        write("You lack the adequate privileges to do that.");
        tell_room(this_object(), this_player()->GetName()+" is "+
                "trying to muck around with the privacy field system.");
        return 1;
    }
    if(!str || str == ""){
        if(privacy) str = "off";
        else str = "on";
    }
    if(str=="on" || str == "1"){
        set_privacy(1);
        write("You enable the privacy field.\n");
        say(this_player()->GetName()+" enables a privacy force field "
                "around the room.");
        return 1;
    }
    if(str=="off" || str == "0"){
        set_privacy(0);
        write("You disable the privacy field.\n");
        say(this_player()->GetName()+" disables a privacy force field "
                "around the room.");
        return 1;
    }
}


