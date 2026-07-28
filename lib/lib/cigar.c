#include <lib.h>

inherit LIB_BURN;
inherit LIB_ITEM;
inherit LIB_SMOKE;

int lastpuff;

protected void create(){
    item::create();
    burn::create();
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

