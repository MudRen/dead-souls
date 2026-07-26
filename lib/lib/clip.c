#include <lib.h>
#include "include/clip.h"
#include <vendor_types.h>
inherit LIB_STORAGE;
inherit LIB_LOAD;
private int caliber, millimeter, MaxAmmo, ammo;
private string firearmtype,ammotype;
void create(){
    ::create();
    SetKeyName("magazine");
    SetId(({"clip","magazine"}));
    SetAdjectives(({"ammunition","pistol"}));
    SetShort("一个手枪弹匣");
    SetLong("这是一个细长的弹簧装填容器，用于半自动手枪弹药。");
    SetMass(10);
    SetValue(1);
    SetVendorType(VT_TREASURE);
}
int CanReceive(object ob){
    string *namen;
    namen=ob->GetId();
    if(member_array("bullet",namen) == -1){
        write("只有子弹才能装入弹匣。");
        return 0;
    }
    if(ob->GetAmmoType() != this_object()->GetAmmoType() ){
        write("这种弹药不适合这个弹匣。");
        return 0;
    }
    if(ob->GetMillimeter() != this_object()->GetMillimeter() ){
        write("这种弹药的尺寸不适合这个弹匣。");
        return 0;
    }
    if(ob->GetCaliber() != this_object()->GetCaliber() ){
        write("这种弹药的口径不适合这个弹匣。");
        return 0;
    }
    if(ob->GetFirearmType() != "auto"){
        write("这种弹药不是半自动弹药。");
        return 0;
    }
    if(sizeof(all_inventory()) >= MaxAmmo){
        write("弹匣已经装满了。");
        return 0;
    }
    ammo++;
    return 1;
}
int CanRelease(object ob){
    ammo--;
    return 1;
}
int MinusAmmo(int i){ ammo -= i; return 1; }
int PlusAmmo(int i){ ammo += i; return 1; }
int SetMaxAmmo(int i){ MaxAmmo=i; return 1; }
int SetFirearmType(string str){firearmtype=str; return 1; }
int SetAmmoType(string str){ammotype=str; return 1; }
int SetCaliber(int x){ caliber=x; return 1; }
int SetMillimeter(int x){ millimeter=x; return 1; }
int GetMillimeter(){ return millimeter; }
int GetCaliber(){ return caliber; }
string GetFirearmType(){ return firearmtype; }
string GetAmmoType(){ return ammotype; }

varargs mixed eventLoad(object who, object where){
    int success, err;
    mixed type = where->GetFirearmType();
    if(base_name(where) != LIB_FIREARM &&
            !inherits(LIB_FIREARM,where)){
        write("这个弹匣是用于枪械的。");
        return 1;
    }
    if(!stringp(type) || type != "auto"){
        write("这个弹匣用于自动枪械。");
        return 1;
    }
    if(where->GetCaliber() != GetCaliber()){
        write("口径不对。");
        return 1;
    }
    if(where->GetMaxLoaded()){
        write("它已经装有弹匣了。");
        return 1;
    }
    err = catch(success = eventMove(where) );
    if(err || !success){
        write("装填时似乎出了问题。");
        return 1;
    }
    else {
        write("你装填了你的 "+where->GetFirearmName()+"。");
        say(this_player()->GetName()+" 将一个弹匣装入了 "+
                possessive(this_player())+" "+
                where->GetFirearmName()+"。");
        where->SetLoaded(1);
    }
    return 1; 
}

varargs mixed eventUnload(mixed where){
    int success, err, inv;
    object env;
    mixed type = where->GetFirearmType();
    object prev = previous_object();
    env = environment();
    if((base_name(previous_object()) == LIB_ROUND ||
                inherits(LIB_ROUND, previous_object())) && intp(where)){
        if(!(inv = sizeof(all_inventory()))){
            write("它已经完全卸空了。");
            return 1;
        }
        if(inv < where) where = inv;
        err=catch(success=all_inventory()[0..inv-1]->eventMove(this_player()));
        if(err || !success){
            write("看来你没能卸下所有想卸的弹药。");
            return 1;
        }
        else {
            write("你从 "+remove_article(GetShort())+" 中卸下了 "+cardinal(where)+" "+
                    remove_article(previous_object()->GetShort())+"。");
            return 1;
        }
    }
    if(!env) return 0;
    if(!type) type = env->GetFirearmType();
    if(!stringp(type)){
        write("这个弹匣不在枪械中。");
        return 1;
    }
    if(env != where){
        write("你似乎搞不清楚要从哪里卸下什么。");
        return 1;
    }
    env = environment(env);
    if(!env || env != this_player()){
        write("你离枪械不够近。");
        return 1;
    }
    err = catch(success = where->eventUnload(env) );
    if(err || !success){
        write("卸载时似乎出了问题。");
        return 1;
    }
    else {
        where->SetLoaded(0);
    }
    return 1;
}
