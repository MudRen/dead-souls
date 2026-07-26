#include <lib.h>
#include <events.h>

inherit LIB_ITEM;
inherit LIB_ROLL;
inherit LIB_SHAKE;
inherit LIB_CONSULT;

int Denominator = 6;
int Result = 6;
string BaseLong;

int SetDenominator(int denom){
    if(!denom) return;
    else return Denominator = denom;
}

mixed SetLong(mixed str){
    item::SetLong(str);
    if(!BaseLong) BaseLong = str;
    return BaseLong;
}

protected void create(){
    item::create();
    SetKeyName("die");
    SetId(({"dado","bone", "alea"}));
    SetShort("一个六面骰子");
    SetLong("这是一个用于赌博游戏的普通骰子。它是橙色的，上面标有数字而不是圆点。");
    SetDenominator(6);
    SetNoCondition(1);
}

void init(){
    item::init();
    if(member_array("d"+Denominator,GetId()) == -1){
        SetId(GetId()+({ "d"+Denominator }) );
    }
}

int doRoll(){
    Result = random(Denominator)+1;
    SetLong(BaseLong + "\n骰子的结果是: "+Result+"。\n");
    return Result;
}

int eventMove(mixed dest){
    int ret;
    if(ret = (item::eventMove(dest))){
        doRoll();
    }
    return ret;
}

varargs mixed eventResults(mixed args){
    if(intp(args)){
        say(this_player()->GetName()+" 掷骰的结果是: "+args);
        write("你掷骰的结果是: "+args);
    }
    return args;
}

varargs mixed eventRoll(object where){
    object dude = this_player();
    string extrathing = "";
    doRoll();
    if(where == environment(this_player())) where = 0;
    if(!where) eventMove(environment(this_player()));
    else {
        if(objectp(where)) extrathing = " on "+where->GetShort();
        if(!inherits(LIB_SURFACE,where) || !eventMove(where)){
            extrathing = "";
            eventMove(environment(this_player()));
        }
    }
    write("你掷出了你的 "+strip_article(GetShort())+extrathing+"，结果是: "+Result);
    say(dude->GetName()+" 掷出了 "+possessive(dude)+" "+strip_article(GetShort())+extrathing+"，"
            "结果是: "+Result);
    return Result;
}

varargs mixed eventShake(object dude, string foo){
    write("你摇了摇你的 "+strip_article(GetShort())+"。");
    say(dude->GetName()+" 摇了摇 "+possessive(dude)+" "+strip_article(GetShort())+"。");
    doRoll();
    return 1;
}

varargs mixed eventConsult(object dude, string foo){
    write("骰子的结果是: \n"+Result);
    say(dude->GetName()+" 查看了 "+possessive(dude)+" "+strip_article(GetShort())+"。");
    return 1;
}

varargs mixed CanConsult(object who, string component){
    return 1;
}

varargs mixed CanShake(object who, string component){
    return 1;
}
