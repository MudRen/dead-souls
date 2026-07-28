#include <lib.h>
#include ROOMS_H
inherit LIB_ITEM;

int traptype = 0;
int traplevel = 0;
int autoresets = 0;
string shadow_object = "";

int SetTrapType(int i){
    traptype = i;
    return traptype;
}

int GetTrapType(){
    return traptype;
}

int SetAutoResets(int i){
    autoresets = i;
    return autoresets;
}

int GetAutoResets(){
    return autoresets;
}

string SetShadowObject(string str){
    if(last(str,2) == ".c") str = truncate(str,2);
    if(!file_exists(str+".c")) error("Cant find  shadow file: "+str+".c");
    if(strsrch(str,"/shadows/")) error("Invalid location for a shadow file.");
    shadow_object = str;
    return shadow_object;
}

string GetShadowObject(){
    return shadow_object;
}

void create(){
    item::create();
    SetId( ({ "trap", "sample trap" }) );
    SetAdjectives( ({ "simple","sample" }) );
    SetShort("一个示例陷阱");
    SetLong("这是一个简单的示例陷阱。");
    SetMass(50);
    SetBaseCost(500);
    SetNoCondition(1);
}

void init(){
    item::init();
}

varargs mixed CanBoobytrap(object who, mixed what){
    if(!environment() || environment() != who) 
        return "#你没有那个东西。";
    //return 0;
    return 1;
}

varargs int eventBoobytrap(object who, mixed target, mixed trap){
    object shadowtrap;
    if(stringp(target)) target = to_object(target);
    if(!target){
        write("那个东西似乎无法安装陷阱。");
        return 1;
    }
    if(living(target)){
        write("你不能对活物安装陷阱。");
        return 1;
    }
    shadowtrap = new(shadow_object);
    if(!shadowtrap){
        write("陷阱有问题。你安装失败了。");
        return 1;
    }
    if(this_player()){
        if(this_player()->GetSkill("concealment"))
            traplevel += this_player()->GetSkill("concealment")["level"];
        traplevel += random(this_player()->GetStat("luck")["level"]);
        traplevel += this_player()->GetStat("coordination")["level"];
        write("你用你的"+remove_article(trap->GetShort())+"在"+target->GetShort()+"上安装了陷阱。");
        say(this_player()->GetCapName()+"似乎在"+target->GetShort()+"上.attach了什么东西。");
    }

    shadowtrap->SetTrapDescription(this_object()->GetLong());
    shadowtrap->SetTrapType(traptype);
    shadowtrap->SetTrapLevel(traplevel);
    shadowtrap->SetAutoResets(autoresets);
    shadowtrap->eventShadow(target);
    this_object()->eventMove(ROOM_FURNACE);
    return 1;
}
