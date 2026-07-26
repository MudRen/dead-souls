#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int privacy, timer;
string ExtraDesc();
protected void create() {
    string privs;
    privs = query_privs();
    if( privs ) privs = capitalize(privs);
    else privs = "a creator";
    room::create();
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("会议室");
    SetLong((: ExtraDesc :));
    SetExits( ([ 
                ]) );
    SetInventory(([
                "/domains/town/obj/bbucket" : 1,
                "/domains/town/obj/chair" : 4,
                "/domains/campus/obj/podium" : 1,
                ]));

    SetProperties(([
                "no attack" : 1,
                "nopeer" : 1,
                ]));
    privacy=0;
    set_heart_beat(20);
    timer = 0;

}

int AutoDeactivate(){
    message("info","%^RED%^隐私力场关闭了。%^RESET%^", this_object());
    timer = 0;
    privacy = 0;
    return 1;
}

void init(){
    ::init();
    add_action("report_time","timer");
}

void heart_beat(){
    if(timer && (time() - timer ) > 1200) AutoDeactivate();
}

int report_time(){
    int secs = time() - timer;

    if(!timer){
        write("隐私力场未激活。");
        return 1;
    }

    write("经过秒数："+secs);
    write("经过分钟："+(secs/60));
    return secs;
}

int CanReceive(object ob) {
    if(privacy){
        if(!interactive(ob)) { 
            message("info","\n\n隐私警告："+ob->GetName()+"进入了房间。\n\n",this_object() );
        }
        else if(!archp(ob)){
            message("info","你被会议室隐私力场弹开了。", ob);
            message("info",ob->GetName()+"被隐私力场弹开了。",this_object());
            if(!environment(ob)) ob->eventMoveLiving(ROOM_START);
            return 0;
        }

    }
    return ::CanReceive(ob);
}

int set_privacy(int i){
    if(environment(this_player()) != this_object() && !archp(this_player())) {
        write("你没有足够的权限执行此操作。");
        say(this_player()->GetName()+"正在试图干扰隐私力场系统。");
        return 1;
    }
    privacy=i;
    timer = time();
    return 1;
}
/*
   int privacy(string str){
   if(environment(this_player()) != this_object() && !archp(this_player())) {
   write("You lack the adequate privileges to do that.");
   say(this_player()->GetName()+" is trying to muck around with the privacy shield system.");
   return 1;
   }

   if(str=="on" || str == "1"){
   this_object()->set_privacy(1);
   write("You enable the privacy shield.\n");
   say(this_player()->GetName()+" enables a privacy force field around the room.");
   timer = time();
   return 1;
   }
   if(str=="off" || str == "0"){
   this_object()->set_privacy(0);
   write("You disable the privacy shield.\n");
   say(this_player()->GetName()+" disables a privacy force field around the room.");
   timer = 0;
   return 1;
   }
   }
 */
int get_privacy(){
    return privacy;
}

string ExtraDesc(){
    string extra = "%^YELLOW%^隐私力场正在此房间周围激活。%^RESET%^";
    string desc = "这是一个附魔房间，拥有阻止不速之客进入的魔法力量。它用于三人或更多人需要不受干扰地或私下分享信息的会议。要启用隐私，请输入 'privacy on'。要禁用隐私，请输入 'privacy off'。隐私力场大约20分钟后自动停用。\n";
    if(privacy) return desc+extra;
    else return desc+"%^RED%^隐私力场已禁用。";
}
