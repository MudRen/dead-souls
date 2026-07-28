#include "include/firearm.h"
#include <lib.h>
#include <damage_types.h>
#include <dirs.h>
inherit LIB_STORAGE;
inherit LIB_LOAD;

private int MaxAmmo, Millimeter, AmmoSize;
private string FirearmType, AmmoType;
private string AmmoFile, firearm_name;
private float Caliber;
private string *namen;
private string *ammonamen;
private int loaded, rounds;
private int shells, magnum;
private int mag,cloned;
private int autohit;
private int dam, last_shot;

protected void create(){
    string *s_save, *a_save;

    ::create();

    s_save = storage::GetSave();
    a_save = s_save;

    AddSave( a_save );
    AddSave( ({ "loaded", "rounds", "shells" , "mag" , "cloned" }) );
    MaxAmmo=6;
    AmmoFile="/domains/default/obj/round";
    FirearmType="revolver";
    AmmoType="round";
    loaded=1;
    rounds=0;
}

void init(){
    object ob;
    object *inv;
    ::init();
    this_object()->CalculateAmmoSize();
    namen=this_object()->GetId();
    if(FirearmType=="revolver"
            && !present("cylinder",this_object())){
        new("/lib/cylinder")->eventMove(this_object());
    }
    if(FirearmType=="revolver" && !cloned){
        cloned=1;
        ob=present("cylinder", this_object());
        inv=all_inventory(ob);
        filter(inv, (: this_object()->InitRevolver($1->GetId()) :) );
    }
    if(FirearmType=="auto" && !present("clip",this_object()) ){
        mag=0;
        loaded=0;
        rounds=0;
    }
}

string SetFirearmName(string str){
    if(str) firearm_name = str;
    return firearm_name;
}

string GetFirearmName(){
    if(firearm_name) return firearm_name;
    return GetKeyName();
}

int InitRevolver(string *arr){
    if(member_array("round",arr) != -1){
        rounds++;
        return 1;
    }
    if(member_array("shell",arr) != -1){
        shells++;
        return 1;
    }
}
mixed CanGetFrom(object who, object item){
    return "不能这样做。试试卸载它。";
}

mixed CanPutInto(object who, object what){
    return "不能这样做。试试给"+GetFirearmName()+"装弹。";
}

int CanReceive(object ob){
    string *idarray;
    if(FirearmType=="revolver"){
        if(rounds == MaxAmmo){
            write("它已经装满弹药了。");
            return 1;
        }
    }
    if(FirearmType != "auto" && ob->GetKeyName() != "revolver cylinder"){
        write("这个"+GetFirearmName()+"只能装子弹。");
        return 0;
    }
    idarray=ob->GetId();
    if(FirearmType=="auto" && member_array("magazine",idarray) == -1){
        write("这个"+GetFirearmName()+"只能装弹夹。");
        return 0;
    }
    if(FirearmType=="auto" && ob->GetMillimeter() != this_object()->GetMillimeter() ){
        write("弹夹尺寸不匹配。");
        return 0;
    }
    if(FirearmType=="auto" && ob->GetCaliber() != this_object()->GetCaliber() ){
        write("弹夹口径不匹配。");
        return 0;
    }
    if(FirearmType=="auto" && ob->GetAmmoType() != this_object()->GetAmmoType() ){
        write("弹夹类型不匹配。");
        return 0;
    }
    if(FirearmType=="auto" && mag){
        write("这个"+GetFirearmName()+"已经装弹了。");
        return 0;
    }
    if(FirearmType=="auto"){
        mag=1;
        rounds=sizeof(all_inventory(ob));
    }
    return 1;
}
int CanRelease(object ob){
    if(ob->GetKeyName()=="revolver cylinder"){
        return 0;

    }
    return 1;
}

varargs mixed eventShoot(object ob, mixed target, string dir, string whom){
    object cible;
    object shell;
    object *obs;

    if(!target || dir){
        write("这件武器不能往那个方向射击。");
        return 1;
    }

    if(objectp(target)){
        cible = target;
    }
    else {
        obs = filter(get_livings(environment(this_player())),
                (: answers_to($(target), $1) :));
        if(!sizeof(obs)) cible = present(target,environment(this_player()));
        else cible = obs[0];
    }
    if(cible) target = cible->GetName();

    else {
        write("似乎无法锁定目标"+target+"。");
        return 1;
    }

    if(!rounds || rounds == 0){
        write("你的武器没有装弹。\n");
        say(environment(this_object())->GetName()+"试图用一把空枪射击"+capitalize(target)+"。\n");
        return 1;
    }
    write("你向"+capitalize(target)+"开枪！\n");
    say(environment(this_object())->GetName()+"向"+capitalize(target)+"开枪！\n");
    if(cible) tell_object(cible, environment(this_object())->GetName()+
            "向你开枪！\n");
    this_object()->eventFire(target);
    if(FirearmType=="auto"){
        shell = new(LIB_SHELL);
        if(!shell) return 1;
        shell->SetFirearmType(GetFirearmType());
        shell->SetCaliber(GetCaliber());
        shell->eventMove(environment(environment(this_object())));
    }
    return 1;
}

int eventFire(mixed str){
    object ob;
    object *obs;
    int tempclass, i, dex;
    int TorsoNum, NumLimbs;
    mixed dexmap;
    string tempshort,templong;
    string *limbarr;
    int limbhit;
    string limbname;
    string s1,s2;
    rounds--;
    if(this_object()->GetFirearmType() == "auto"){
        if(first_inventory(present("magazine",this_object())) ){
            first_inventory(present("magazine",this_object()))->eventDestruct();
            present("magazine",this_object())->MinusAmmo(1);
        }
        else rounds=0;
    }
    if(this_object()->GetFirearmType() == "revolver"){
        shells++;
        ob=present("cylinder",this_object());
        if(present("round",ob)) present("round",ob)->eventDestruct();
        new("/lib/shell")->eventMove(ob);
    }
    if(rounds <= 0) loaded=0;
    ob = 0;
    if(objectp(str)) ob = str;
    else obs = filter(get_livings(environment(this_player())),
            (: answers_to($(str), $1) :));
    if(!ob && !sizeof(obs)) ob = present(str,environment(this_player()));
    else if(!ob) ob = obs[0];
    if(creatorp(ob)){
        write(ob->GetName()+"用牙齿接住了你的子弹。\n");
        say(ob->GetName()+"用牙齿接住了子弹。\n");
        autohit=0;
        return 1;
    }
    if(ob && !living(ob) && base_name(ob) != LIB_CORPSE){
        tell_room(environment(environment(this_object())),
                "子弹击碎了"+lower_case(ob->GetShort())+"！\n");
        if(!sscanf(ob->GetLong(),"%sIt has been damaged by gun%s",s1,s2)){
            tempclass=ob->GetClass();
            if(tempclass) ob->SetClass(tempclass/2);
            tempshort=ob->GetShort();
            tempshort = "a damaged "+remove_article(tempshort);
            ob->SetShort(tempshort);
            templong=ob->GetLong();
            if(sscanf(templong,"%s\n\n%s",s1,s2) >=1){
                templong=s1+" It has been damaged by gunfire.\n\n";
            }
            else
                templong += " It has been damaged by gunfire.";
            ob->SetLong(templong);
            return 1;
        }
        tempclass=ob->GetClass();
        if(tempclass) ob->SetClass(tempclass/2);
        return 1;
    }
    i = random(100);
    if(!creatorp(environment())){
        dex = environment(this_object())->GetStatLevel("coordination");
        dex += (environment(this_object())->GetStatLevel("luck") / 3);
        if(environment(this_object())->GetSkillLevel("firearms") < 10){
            int now = time();
            if(last_shot == now) dex -= 100;
            else if((now - last_shot) < 2)  dex -= 50;
        }
    }
    else dex = 200;
    last_shot = time();
    if((ob && living(ob)) && (i < dex || autohit==1)){
        if(random(2)) limbname = ob->GetTorso();
        else limbname = scramble_array(ob->GetLimbs())[0];
        tell_room(environment(environment(this_object())),"子弹击中了"+
                capitalize(str)+"的"+limbname+"！\n",ob);
        tell_object(ob,"子弹击中了你的"+limbname+"！\n");
        ob->AddLead("gunshot_wounds", 1);
        ob->SetAttack(this_agent());
        if(!present("firearms_wound",ob)){
            new(LIB_WOUND)->eventMove(ob);
        }
        if(Caliber){
            float tmp;
            int extradam = this_object()->GetMagnum();
            if(to_float(Caliber) < 1.00) Caliber = to_float(Caliber) * 100.00;
            if(Caliber > 99) tmp = to_float(Caliber) * 0.10;
            dam = to_int(tmp);
            if(extradam) dam += (random(extradam/2) + extradam/2);
        }
        if(Millimeter){
            dam = Millimeter;
            dam *= random(10);
        }
        if(!dam) dam = 7;

        dam += random(environment(this_object())->GetStatLevel("coordination"));
        dam += environment(this_object())->GetSkillLevel("projectile attack");
        dam -= random(ob->GetStatLevel("luck"));
        dam -= random(ob->GetSkillLevel("projectile defense"));

        if(creatorp(this_player())) write("你造成了 "+dam+" 点伤害");

        ob->eventReceiveDamage(environment(this_object()),(PIERCE), dam, 0, limbname);
        if(!ob->GetInCombat()){
            ob->eventForce("attack "+environment(this_object())->GetKeyName());
        }
        autohit=0;
        return 1;
    }
    write("你的射击没有命中目标。\n");
    say(environment(this_object())->GetName()+"的射击没有命中目标。\n");
    this_object()->missed_shot();
    return 1;
}

int missed_shot(){
    object ob,maghere,magstuff;
    string str;
    int i;
    object *inv;
    string *arr;
    if(environment(environment(this_object()))->GetClimate() != "indoors"){
        return 1;
    }
    inv=all_inventory(environment(environment(this_object())));
    i=random(sizeof(inv));
    if(living(inv[i])){
        tell_room(environment(environment(this_object())), inv[i]->GetName()+"被流弹击中！",inv[i]);
        tell_object(inv[i],"你被"+environment(this_object())->GetName()+
                "的流弹击中了。\n");
    }
    if(!living(inv[i])){
        string shortd = (inv[i]->GetShort() || "");
        arr=explode(inv[i]->GetKeyName(),"");
        if(sizeof(arr) && arr[sizeof(arr)-1] =="s"){
            tell_room(environment(environment(this_object())), 
                    capitalize(shortd)+" are struck by the stray bullet.");
        }
        else
            tell_room(environment(environment(this_object())),
                    capitalize(shortd)+" is struck by the stray bullet.");
    }
    autohit=1;
    rounds++;
    this_object()->eventFire(inv[i]->GetKeyName());
    if(this_object()->GetFirearmType() == "revolver"){
        shells--;
        present("shell",present("cylinder",this_object()))->eventDestruct();
        ob=new("/lib/round");
        ob->SetCaliber(this_object()->GetCaliber());
        ob->SetMillimeter(this_object()->GetMillimeter());
        ob->SetFirearmType(this_object()->GetFirearmType());
        ob->SetAmmoType(this_object()->GetAmmoType());
        ob->eventMove(present("cylinder",this_object()));
    }
    else
    {
        str = "";
        maghere=present("magazine",this_object());
        if(maghere) magstuff = first_inventory(maghere);
        if(maghere && magstuff) str=base_name(magstuff);
        if(str && str !="" )	new(str)->eventMove(maghere);
    }
    return 1;
}
int CalculateAmmoSize(){
    float i;
    i=this_object()->GetCaliber();
    if(i > 0){
        if(stringp(i)) sscanf(i,"%d",i);
        if(intp(i)) to_float(i);
        while(i > 1.0){
            i = i*(0.1);
        }
        i = i*(25.4);
        AmmoSize=to_int(i);
        dam=AmmoSize*(AmmoSize);
        dam *= 3;
        return 1;
    }
    AmmoSize=this_object()->GetMillimeter();
    return 1;
}
int ShowRounds(){ environment(this_object())->eventPrint("武器剩余："+rounds+" 发子弹。\n");
    environment(this_object())->eventPrint("武器剩余："+shells+" 发弹壳。\n");
    return 1;
}
int SetAmmo(int i){ rounds=i; return 1; }
int GetAmmo(){ return rounds; }
int GetMag(){ return mag; }
int SetMag(int i){ mag=i; return 1; }
int SetLoaded(int i){ loaded=i; return 1; }
int GetLive(){ return loaded; }
int SetAmmoFile(string str){ AmmoFile=str; return 1; }
int SetAmmoType(string str){ AmmoType=str; return 1; }
int SetFirearmType(string str){ FirearmType=str; return 1; }
int SetMaxAmmo(int x){ MaxAmmo=x; return 1; }
int SetCaliber(int x){ Caliber=x; return 1; }
int SetMillimeter(int x){ Millimeter=x; return 1; }
string GetAmmoType(){ return AmmoType; }
string GetFirearmType(){ return FirearmType; }
int GetMaxAmmo(){ return MaxAmmo; }
int GetCaliber(){ return Caliber; }
int GetMillimeter(){ return Millimeter; }

mixed eventLoad(object ob){
    mixed can = CanLoad(this_player());
    if(!can || !intp(can)) return 0;
    if(!ob || !objectp(ob) || (objectp(ob) && living(ob))){
        write("用什么来给"+GetKeyName()+"装弹？");
        return 1;
    }
    if(GetFirearmType() == "revolver" && ob && objectp(ob) &&
            ob->GetFirearmType() == "revolver" && (base_name(ob) == LIB_ROUND ||
                inherits(LIB_ROUND,ob)) && ob->GetCaliber() == GetCaliber() &&
            rounds != MaxAmmo){
        rounds++;
    }
    return 1;
}

mixed eventUnload(mixed what){
    string n1,s1,s2;
    int n2;
    mixed can = CanUnload(this_player());
    if(!can || !intp(can)) return 0;

    if(FirearmType=="auto" && !mag){
        write("它已经卸过了。");
        return 1;
    }
    if(mag==1 && environment(this_object()) == this_player()){
        this_object()->doMagUnload();
        return 1;
    }
    if(FirearmType=="revolver" && 
            environment(this_object()) == this_player()){
        if(rounds == 0 && shells == 0){
            write("你的"+GetFirearmName()+"已经是空的了。");
            return 1;
        }
        if(intp(what) && what < 7 && what > 0) true();
        else what = "all";
        write("你卸下了你的"+GetFirearmName()+"。");
        this_object()->doRevolverUnload("all",what);
        return 1;
    }
}

int doMagUnload(){
    if(!present("clip",this_object())){
        write("这个"+GetFirearmName()+"已经是空的了。");
        return 0;
    }
    write("你从你的"+GetFirearmName()+"上卸下了一个弹夹。");
    say(this_player()->GetName()+"从"+possessive(this_player())+"的"+GetFirearmName()+"上卸下了一个弹夹。");
    present("clip",this_object())->eventMove(environment(this_object()));
    mag=0;
    loaded=0;
    rounds=0;
    return 1;
}

int doRevolverUnload(string what, string num){
    int i,n1,n2;
    if(sscanf(num,"%d",n1)){
    }
    if(what=="all"){
        n1=shells;
        n2=rounds;
    }
    if(what=="shells" || what=="all"){
        i=shells-n1;
        while(shells > i){
            present("shell",present("revolver cylinder",this_object()))->eventMove(environment(this_object()));
            shells--;
        }
    }
    if(what=="rounds" || what=="all"){
        if(what != "all") n2=n1;
        i=rounds-n2;
        while(rounds > i){
            present("round",present("revolver cylinder",this_object()))->eventMove(environment(this_object()));
            rounds--;
        }
    }
    if(n2 > 0){
        string things = "rounds";
        if(n2 == 1) things = "round";
        write("你从你的"+GetFirearmName()+"里退出了"+cardinal(n2)+"发"+things+"。");
    }
    if(n1 > 0){
        string things = "shells";
        if(n1 == 1) things = "shell";
        write("你从你的"+GetFirearmName()+"里退出了"+cardinal(n1)+"发"+things+"。");
    }
    say(environment(this_object())->GetName()+"从"+
            possessive(environment(this_object()))+"左轮手枪里退出了一些弹药。");
    return 1;
}

int GetMaxLoaded(){
    if(rounds + shells >= MaxAmmo) return 1;
    return 0;
}

int GetMagnum(){
    return magnum;
}

int SetMagnum(int i){
    if(i > 0) magnum = i;
    else magnum = 0;
    return magnum;
}

