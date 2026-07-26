#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_INSTALL;

varargs int eventCloak(mixed arg);
varargs int eventDecloak(mixed arg);

int power = 0;
function f1 = 0;
function f2 = 0;
mapping SendMap = ([]);

void create(){
    item::create();

    SetKeyName("data module");
    SetId( ({"module", "cartridge"}) );
    SetAdjectives( ({"data","yautja","stealth"}) );
    SetShort("一个 Yautja 数据模块");
    SetLong("这是一个 small cartridge that contains programming intended for a Yautja wrist computer。它 appears to have writing on it。");
    SetNoCondition(1);
    SetMass(1);
    SetReads( ([
                "default" : "隐身模块：提供隐身和显形功能。",
                "writing": "隐身模块：提供隐身和显形功能。",
                ]) );
    SetLanguage("Yautja");
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
}

varargs int eventDecloak(mixed arg){
    int ret;
    string s1,s2;
    string *hist = environment(this_object())->GetHist();
    if(!arg) arg = this_player();
    if(!environment() || !(environment()->GetWorn())){
        write("你没有 wearing the wrist computer。");
        return 1;
    }
    if(!power){
        write("计算机未激活。");
        return 1;
    }
    //write("%^GREEN%^last command:%^RESET%^ "+arg->GetCurrentCommand());
    arg = arg->GetCurrentCommand();
    if(sscanf(arg,"%s %s",s1,s2) == 2){
        if(s2 == "on" || s2 == "disable"){
            eventCloak(this_player());
            return 1;
        }
    }
    if(!(this_player()->GetInvis())){
        write("你的腕式电脑 chirps， and nothing happens。");
        say(this_player()->GetName()+"的腕式电脑 chirps。");
        return 1;
    }
    write("你的腕式电脑 chirps， and you become visible。");
    say(this_player()->GetName()+"的腕式电脑 chirps， and "+capitalize(this_player()->GetKeyName())+" fades into view。");
    this_player()->SetInvis(0);
    return 1;
}

varargs int eventCloak(mixed arg){
    int ret;
    string s1,s2;
    string *hist = environment(this_object())->GetHist();
    if(!arg) arg = this_player();
    if(!environment() || !(environment()->GetWorn())){
        write("你没有 wearing the wrist computer。");
        return 1;
    }
    if(!power){
        write("计算机未激活。");
        return 1;
    }
    //write("%^YELLOW%^last command:%^RESET%^ "+arg->GetCurrentCommand());
    arg = arg->GetCurrentCommand();
    if(sscanf(arg,"%s %s",s1,s2) == 2){
        if(s2 == "off" || s2 == "disable"){
            eventDecloak(this_player());
            return 1;
        }
    }
    if(this_player()->GetInvis()){
        write("你的腕式电脑 chirps， and nothing happens。");
        say(this_player()->GetName()+"的腕式电脑 chirps。");
        return 1;
    }
    write("你的腕式电脑 chirps， and you become transparent。");
    say(this_player()->GetName()+"的腕式电脑 chirps， and "+nominative(this_player())+" fades from view。");
    this_player()->SetInvis(1);
    return 1;
}

varargs mixed eventInstall(object what, object where, int auto){
    f1 = (: eventCloak(this_player()) :);
    f2 = (: eventDecloak(this_player()) :);
    if(!where){
        write("安装到哪里？");
        return 1;
    }
    SendMap = ([
            "cloaking" : ([ "function" : f1, "hook" : "cloak" ]),
            "decloaking" : ([ "function" : f2, "hook" : "decloak" ])
            ]);
    where->eventInstallModule(SendMap,auto ||0);
    power = 1;
    return 1;
}

varargs mixed eventUninstall(object what, mixed auto){
    int success;
    what->eventUninstallModule(this_object(), auto || 0);
    if(this_player() && environment() && environment() == what)
        success = this_object()->eventMove(this_player());
    if(success || auto) return 1;
    else {
        //if(!success) write("The uninstall failed.");
        return 0;
    }
}

string Report(){
    string ret = "";
    if(!sizeof(SendMap)) return ret;
    foreach(mixed key, mixed val in SendMap){
        ret += "Functionality: "+key+", command: "+val["hook"]+"\n";
    }
    return ret;
}

int eventPowerOff(){
    object whom = this_player();
    object env = environment();
    power = 0;
    if(env) env->eventUninstallModule(this_object(),1);
    else return 0;
    if(!whom) whom = environment(env);
    if(!whom) return 0;
    else {
        if(living(whom)){
            if(whom->GetInvis() && !creatorp(whom)){
                whom->SetInvis(0);
                tell_object(whom, "你的腕式电脑发出 croaking noise， and you become visible。");
                tell_room(environment(whom),whom->GetName()+"的腕式电脑发出 croaking noise， and "+capitalize(whom->GetKeyName())+" fades into view。", whom);
            }
        }
    }
    return 1;
}

int eventPowerOn(){
    object env = environment();
    power = 1;
    if(env) env->eventInstallModule(SendMap,1);    
    return 1;
}

void init(){
    ::init();
}
