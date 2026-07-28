#include <lib.h>

inherit LIB_ITEM;
inherit LIB_SMOKE;
inherit LIB_BURN;

private int BurnRate = 5;
int lastpuff;

protected void create(){
    item::create();
    burn::create();
}

protected void heart_beat(){
    eventDecreaseFuel(1);
    if( GetFuelAmount() < 1){
        eventBurnOut();
    }
}

mixed direct_light_obj(){
    mixed tmp = CanBurn(this_player());

    if( tmp == 1 ){
        return "用什么点燃它？";
    }

    if( GetFuelAmount() < 1 )
        return GetShort()+"里没有" + GetFuelType() + "。";
    return 1;
}

mixed eventDarken(){
    burn::eventDarken();
    set_heart_beat(0);
    return 1;
}

varargs mixed eventLight(object who, object tool){
    if( GetLit() ) return burn::eventLight(who, tool);
    burn::eventLight(who, tool);
    set_heart_beat(BurnRate);
    return 1;
}

int GetBurnRate(){
    return BurnRate;
}

protected int SetBurnRate(int x){
    return (BurnRate = x);
}

int GetRadiantLight(int ambient){
    if( !GetLit() ) return 0;
    else return item::GetRadiantLight(ambient);
}

string GetShort(){
    return item::GetShort() + burn::GetShort();
}

varargs string GetLong(string unused){
    string tmp;

    tmp = burn::GetLong(unused);
    if( tmp != "" ) return item::GetLong(unused) + "\n" + tmp;
    else return item::GetLong(unused);
}

int GetLastPuff(){
    return lastpuff;
}

mixed eventSmoke(object who, object what){
    if(!GetLit()){
        write("它没有点燃！");
        return 1;
    }
    write("你吸了一口你的"+remove_article(GetShort())+"。");
    say(who->GetName()+"吸了一口"+possessive(who)+" "
            +remove_article(GetShort())+"。");
    lastpuff = time();
    eventDecreaseFuel(1);
    if( !GetFuelAmount() ) eventBurnOut();
    return 1;
}
