#include <lib.h>
#include "include/round.h"
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_LOAD;
private int caliber,millimeter;
private string firearmtype,ammotype;
private string rifletype;
void create(){
    ::create();
    SetKeyName("round");
    SetId(({"round","bullet"}));
    SetShort("一发普通手枪弹");
    SetLong("这是一发普通手枪弹。");
    SetMass(1);
    SetValue(1);
    SetVendorType(VT_TREASURE);
}
int SetRifleType(string str){rifletype=str; return 1; }
int SetFirearmType(string str){firearmtype=str; return 1; }
int SetAmmoType(string str){ammotype=str; return 1; }
int SetCaliber(int x){ caliber=x; return 1; }
int SetMillimeter(int x){ millimeter=x; return 1; }
int GetMillimeter(){ return millimeter; }
int GetCaliber(){ return caliber; }
string GetRifleType(){ return rifletype; }
string GetFirearmType(){ return firearmtype; }
string GetAmmoType(){ return ammotype; }

varargs mixed eventLoad(object who, object where){
    int success, err;
    object cylinder;
    mixed type;
    if(where) type = where->GetFirearmType();
    else {
        write("装到哪里？");
        return 0;
    }
    if(!stringp(type) && !stringp(type = where->GetAmmoType())){
        write("这个似乎不适合用来装填。");
        return 1;
    }
    if(type == "acp"|| type == "nato") type = "auto";
    if(type == "revolver"){
        mixed tmparr = filter(all_inventory(where),
                (: base_name($1) == LIB_CYLINDER || inherits(LIB_CYLINDER, $1) :) );
        if(sizeof(tmparr)) cylinder = tmparr[0];
    }
    if(GetFirearmType() == "revolver" && ((base_name(where) != LIB_FIREARM &&
                    !inherits(LIB_FIREARM,where)) || type != "revolver")){
        write("这种弹药是给左轮手枪用的。");
        return 1;
    }
    if(GetFirearmType() == "auto" && (base_name(where) == LIB_FIREARM ||
                inherits(LIB_FIREARM,where))){
        write("那种武器使用弹夹供弹。");
        return;
    }
    if(where->GetCaliber() != GetCaliber()){
        write("口径不对。");
        return 1;
    }
    if(where->GetMaxLoaded()){
        write("它已经装满弹药了。");
        return 1;
    }
    err = catch(success = eventMove((cylinder || where)) );
    if(err || !success){
        write("装填似乎出了问题。");
        return 1;
    }
    else {
        if(cylinder) where->eventLoad(this_object());
        write("你装填了你的"+where->GetShort()+"。");
        say(this_player()->GetName()+"把"+GetShort()+
                "装入了"+possessive(this_player())+"的"+
                remove_article(where->GetShort())+"。");
    }
    return 1; 
}

varargs mixed eventUnload(object where){
    int success, err;
    object env;
    mixed type = where->GetFirearmType();
    env = environment();
    if(!env) return 0;
    if(base_name(env) == LIB_CYLINDER || inherits(LIB_CYLINDER, env)){
        env = environment(env);
    }
    if(!env) return 0;
    if(!type) type = env->GetFirearmType();
    if(!stringp(type)){
        write(remove_article(GetShort())+"没有被装在任何地方。");
        return 1;
    }
    if(env != where){ 
        write("你似乎搞混了要从哪里卸载。");
        return 1;
    }
    env = environment(env);
    if(!env || env != this_player()){
        write("你离"+
                remove_article(where->GetShort())+"不够近。");
        return 1;
    }
    err = catch(success = where->eventUnload(1) );
    if(err || !success){
        write("卸载似乎出了问题。");
        return 1;
    }
    else {
        where->SetLoaded(0);
    }
    return 1;
}
