#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ACTIVATE;
inherit LIB_INSTALL;
inherit LIB_WORN_STORAGE;

nosave int active = 0;
int lupus;
mapping SpecialFuns = ([]);

int CheckPanel(){
    if(this_object()->GetClosed()){
        write("腕式电脑是关闭的。面板无法访问。");
    }
    else {
        write("一个你可以阅读的面板。");
    }
    return 1;
}

protected void create() {
    worn_storage::create();
    SetKeyName("wrist computer");
    SetId( ({ "computer", "bracer","comp","wristcomp","system" }) );
    SetAdjectives( ({ "wrist","odd","odd looking","complex","tough","rugged",
                "tactical", "tactical data" }) );
    SetShort("一台铁血战士腕式电脑");
    SetLong("一个外形奇特的臂环，设计用于穿戴在手臂上。它看起来"+
            "极其复杂，但同时也非常坚固耐用。也许可以"+
            ""激活护腕"。看起来打开它就能访问特殊功能。");
    SetDamagePoints(75);
    SetVendorType(VT_ARMOR);
    SetMass(10);
    SetBaseCost("silver", 1000);
    SetArmorType(A_CUSTOM);
    SetProtection(BLUNT, 10);
    SetProtection(BLADE, 10);
    SetProtection(KNIFE, 20);
    SetProtection(HEAT, 30);
    SetRestrictLimbs(({"left arm"}));
    SetMaxCarry(100);
    SetCanClose(1);
    SetClosed(1);
    SetLanguage("Yautja");
    SetItems( ([
                ({"panel","functions"}) : (: CheckPanel :),
                ]) );
    SetRead( ([
                ({ "panel", "default" }) :"Yautja tactical data system, version .09",
                //"panel": (: eventRead :),
                ]) );
    SetMaxClones(2);
}

int eventInitialize(){
    object env;
    if(!(env = environment()) || !living(env)) return 0;
    foreach(object module in all_inventory()){
        if(module) module->eventInstall(env, this_object());
    }
    return 1;
}

void init(){
    ::init();
    eventInitialize();
}

int eventMove(mixed arg){
    eventInitialize();
    return ::eventMove(arg);
}

varargs int YautLang(object whom){
    if(!whom) whom = this_player(); 
    if(!whom) return 0;
    if(whom->GetPolyglot()) return 100;
    return whom->GetLanguageLevel("Yautja");
}

varargs void yaut_write(string str, object whom){
    if(!str || !sizeof(str)) return;
    if(!whom) write("%^MAGENTA%^"+translate(str,YautLang())+"%^RESET%^");
    else tell_object(whom,"%^MAGENTA%^"+translate(str,YautLang(whom))+"%^RESET%^");
}

varargs void yaut_say(string str, mixed whom){
    object *exclude = ({});
    object *include = get_livings(environment(this_player()));
    if(whom){
        if(objectp(whom)) exclude = ({ whom });
        else exclude = whom;
    }
    include -= exclude;
    if(sizeof(include))
        foreach(object dude in include){
            yaut_write(str, dude);
        }
}

int eventTurnOn(){
    object *contents = all_inventory();
    if(!(this_object()->GetWorn()) || !this_player() ||
            environment(this_object()) != this_player()){
        write("你没有穿戴腕式电脑。");
        return 1;
    }
    write("你激活了腕式电脑。电脑显示：");
    say(this_player()->GetName()+" operates "+possessive(this_player())+" "
            "wrist computer. You hear the computer say: ");
    yaut_say("Computer online.");
    if(sizeof(contents)) contents->eventPowerOn();
    active = 1;
    return 1;
}

int eventTurnOff(){
    object *contents = all_inventory();
    write("你关闭了腕式电脑。电脑显示：");
    say(this_player()->GetName()+" operates "+possessive(this_player())+" "
            "wrist computer. You hear the computer say: ");
    yaut_say("Computer offline.");
    if(sizeof(contents)) contents->eventPowerOff();
    active = 0;
    return 1;
}

varargs mixed eventInstall(object what, object where){
    write("腕式电脑不能安装到任何地方。");
    return 1;
}

int CanReceive(object ob){
    if(!answers_to("yautja data module",ob)){
        write("那不是这台电脑的正确数据模块。");
        return 0;
    }
    else return 1;
}

varargs mixed eventUninstallModule(object which, int auto){
    object *contents = all_inventory();
    object module = previous_object();
    if(which) module = which;
    if(!auto) say(this_player()->GetName()+" operates "+possessive(this_player())+" "
            "wrist computer.");
    if(!active){
        if(!auto) write("电脑没有激活。");
        return 1;
    }
    if(!auto){
        write("你尝试从腕式电脑中卸载一个模块。电脑显示：");
        say(this_player()->GetName()+"'s wrist computer says: ");
        yaut_say("Uninstalling...");
    }
    if(SpecialFuns[module])
        foreach(mixed key, mixed val in SpecialFuns[module]){
            remove_action("foo",SpecialFuns[module][key]["hook"]);
            if(!auto){
                yaut_say(key+" successfully uninstalled.");
            }
        }
    map_delete(SpecialFuns, module);
    return 1;
}

varargs mixed eventInstallModule(mapping ModuleData, int auto){
    string *contents = ({});
    object module = previous_object();
    if(member_array("eventInitialize",call_stack(2)) != -1) auto = 1;
    if(!auto) say(this_player()->GetName()+" operates "+possessive(this_player())+" "
            "wrist computer.");
    if(!answers_to("Yautja data module",module)){
        if(!auto) write("那不是这台电脑的正确数据模块。");
        return 0;
    }
    if(!active){
        if(!auto) write("电脑没有激活。");
        return 1;
    }
    if(this_object()->GetClosed()){
        write("电脑是关闭的。");
        return 1;
    }
    if(sizeof(all_inventory()))
        foreach(object element in all_inventory()){
            contents += ({ base_name(element) });
        }
    if(member_array(base_name(module),contents) != -1){
        if(!auto){
            write("腕式电脑已经包含了那种类型的模块。");
            return 0;
        }
    }
    SpecialFuns[module] = ModuleData;
    if(!auto){
        write("你将一个模块安装到腕式电脑中。电脑显示：");
        say(this_player()->GetName()+"'s wrist computer says: ");
        yaut_say("Installing...");
    }
    foreach(mixed key, mixed val in SpecialFuns[module]){
        add_action(SpecialFuns[module][key]["function"],SpecialFuns[module][key]["hook"]);
        if(!auto){ 
            yaut_say(key+" successfully installed.");
            module->eventMove(this_object());
        }
    }
    return 1;
}

mixed CanPutInto(object who, object item){
    return "这是一台腕式电脑。可以在上面安装模块。";
}

mixed CanGetFrom(object who, object item){
    return "这是一台腕式电脑。可以从上面卸载模块。";
}

varargs mixed eventRead(mixed who, mixed str){
    object dude;
    string what;
    string ret = "Yautja tactical data system display. Installed modules:\n";
    if(stringp(who)){
        what = who;
        dude = this_player();
    }
    else {
        dude = who;
        what = str;
    }
    if(this_object()->GetClosed()){
        write("腕式电脑是关闭的。没有东西可以阅读。");
        return 1;
    }
    if(!active){
        write("腕式电脑没有激活。");
        return 1;
    }
    foreach(mixed ob in all_inventory()){
        if(ob->Report()) ret += ob->Report();
    }
    if(!lupus && random(99) > 95){
        lupus = 1;
        ret = "BAD WOLF";
    }
    SetRead( ([
                ({ "panel", "default" }) :ret,
                ]) );
    return ::eventRead(dude, what);
}

varargs mixed eventOpen(object who, object tool){
    SetProtection(BLUNT, 1);
    SetProtection(BLADE, 1);
    SetProtection(KNIFE, 2);
    SetProtection(HEAT, 3);
    ::eventOpen(who || 0, tool || 0);
    if(!(this_object()->GetClosed())){
        write("打开腕式电脑露出了一个可以阅读的面板。");
        return 1;
    }
    return 0;
}

mixed eventClose(object who){
    SetProtection(BLUNT, 10);
    SetProtection(BLADE, 10);
    SetProtection(KNIFE, 20);
    SetProtection(HEAT, 30);
    return ::eventClose(who || 0);
}

string GetInternalDesc(){
    return "This is the interface for the wrist computer. You may try to \"read computer\"";
}

varargs mixed eventUnequip(object who){
    object *contents = all_inventory();
    if(sizeof(contents)) contents->eventPowerOff();
    ::eventUnequip(who||0);
}
