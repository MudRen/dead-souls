#include <lib.h>
#include <vendor_types.h>
inherit LIB_STORAGE;
inherit LIB_TURN;

void SetLightLevel(int i);
int eventRadiate(int i);

object player,env,fl;
string me,name, celltype, baseshort;
int noflicker,Lit,lightlevel,drainrate,powered,level;
int mincells, maxcells;

void create(){
    ::create();
    SetKeyName("generic flashlight");
    SetId( ({"fl","flashlight","light","torch","flashlite"}) );
    SetAdjectives( ({"generic","simple","cheap"}) );
    SetShort( "手电筒" );
    SetLong("这是一个廉价、简单的光源。");
    SetMass(20);
    SetBaseCost(10);
    SetLightLevel(6);
    Lit=0;
    mincells = 2;
    maxcells = 2;
    celltype = "D";
    SetVendorType(VT_TREASURE);
    baseshort=GetShort();
}

string GetShort(){
    string ret, str, article;
    string litstr = "%^BOLD%^YELLOW%^(lit)%^RESET%^ ";
    if(!Lit || query_verb() == "activate" || query_verb() == "turn"){
        return ::GetShort();
    }
    if(!(str = ::GetShort()) || str == "") return str;
    article = (replace_string(str, remove_article(str), "") || "");
    str = remove_article(str);
    ret = (sizeof(article) ? article : "") + litstr + str;
    return ret;
}

void init(){
    ::init();
    fl=this_object();
    me=this_object()->GetKeyName();
}

int SetHB(int i){
    set_heart_beat(i);
    return query_heart_beat();
}
int GetHB(){
    return query_heart_beat();
}

int SetMaxCells(int i){ maxcells = i; return i; }
int GetMaxCells(){ return maxcells; }
int SetMinCells(int i){ mincells = i; return i; }
int GetMinCells(){ return mincells; }
int SetCellType(string str){celltype=str; return 1; }
string GetCellType(){ return celltype; }

int SetDrainRate(int i){
    drainrate = i;
    return i;
}

varargs int eventUse(mixed i, mixed foo){
    if(query_verb() == "use"){
        write("不是这样使用的。");
        return 1;
    }
    Lit = i;
    foreach(object ob in all_inventory(this_object())){
        ob->eventUse(i);
    }
    return i;
}

int eventDie(){
    if(!Lit || Lit == 0) return 1;
    Lit=0;
    eventRadiate(0);
    foreach(object ob in all_inventory(this_object())){
        ob->eventUse(0);
    }
    //SetShort(baseshort);
    tell_object(environment(this_object()),me+"闪烁了一下然后熄灭了。");
    if(living(environment())){
        tell_room(environment(environment()),environment()->GetName()+"的"+me+
                "闪烁了一下然后熄灭了。",({ environment() }) );
    }
    set_heart_beat(0);
    return 1;
}

int flicker(){
    if(noflicker ==1) return 0;
    if(!living(environment())){
        tell_object(environment(),capitalize(baseshort)+"闪烁了一下，变得比之前暗淡了。");
        return 1;
    }
    tell_room(environment(environment()),environment()->GetName()+"的"+me+
            "闪烁了一下，变得比之前暗淡了。",({ environment() }) );
    tell_object(environment(),me+"闪烁了一下，变得更暗淡了。");
    return 1;
}

int CheckPower(){
    object *batts;
    powered = 1;
    if( sizeof(all_inventory(this_object())) < mincells ) powered = 0;
    batts = all_inventory(this_object());
    foreach(object batt in batts){
        batt->Spent();
        level = batt->GetCharge();
        if(level == 10 || level == 30 || level == 50 ) flicker();
        noflicker = 1;
        if( level < 1) powered = 0; 
    }
    noflicker = 0;
    return powered;
}

int CanReceive(object ob){
    if(ob->GetCellType() != celltype){
        return 0;
    }
    if(sizeof(all_inventory(this_object())) >= maxcells ){

        return 0;
    }
    return 1;
}

int eventRadiate(int i){
    SetRadiantLight(i);
}

void SetLightLevel(int i){
    if(i) lightlevel = i;
}

int GetLightLevel(){
    if(lightlevel) return lightlevel;
    return 0;
}

void regetID(){
    player=this_player();
    name=this_player()->GetName();
    env=environment(this_object());
}

varargs mixed eventTurn(string str){
    regetID();
    if( player != env ){ write("你没有那个东西。"); return 0; }
    write("你在手中翻转着"+me+"。");
    say(name+"在"+possessive(player)+"手中翻转着一个"+me+"。");
    return 1;
}

int eventTurnOn(object ob){
    regetID();
    CheckPower();

    if(powered != 1){
        write("它没有电源。");
        return 1;
    }

    if(player != env  && environment(player) !=env){
        write("它不在你够得到的地方。");
        return 1;
    }
    if(Lit < 1){
        write("你打开了"+me+"。");
        say(name+"打开了一个"+me+"。");
        if(drainrate && drainrate > 0) eventUse(drainrate);
        else eventUse(1);
        eventRadiate(lightlevel);
        set_heart_beat(1);
        //SetShort(baseshort+" (%^BOLD%^YELLOW%^lit%^RESET%^)");
        return 1;
    }
    if(Lit >= 1){
        write("它已经亮着了。");
        return 1;
    }
}

varargs mixed eventTurnOff(string str){
    regetID();
    if(player != env  && environment(player) !=env){ write("它不在你够得到的地方。"); return 1; }
    if(Lit > 0){
        write("你关掉了"+me+"。");
        say(name+"关掉了"+me+"。");
        eventRadiate(0);
        eventUse(0);
        set_heart_beat(0);
        //SetShort(baseshort);
        return 1;
    }
    if(Lit < 1){
        write("它已经关了。");
        return 1;
    }
}

mixed eventExtinguish(){
    return eventTurnOff("foo");
}

mixed eventLight(){
    return eventTurnOn(this_object());
}

void heart_beat(){
    CheckPower();

    if(powered != 1){
        eventDie();
    }
}
