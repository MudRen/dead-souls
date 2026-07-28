#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <localtime.h>
#include <daemons.h>

inherit LIB_ARMOR;

int eventReadWatch();

protected void create(){
    armor::create();
    SetKeyName("pocket watch");
    SetId(({"watch","pocketwatch","pocket watch","timepiece"}));
    SetShort("一块怀表");
    SetLong("这是一块装饰精美、雕刻细致的 "+
            "怀表。它闪耀着明亮的抛光青铜 "+
            "光泽。它正静静地滴答作响，看起来你可以通过 "+
            "查看怀表来获取准确时间。");
    SetMass(10);
    SetBaseCost("silver",40);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_AMULET);
    SetDefaultRead( (: eventReadWatch :) );
}
void init(){
    ::init();
}

int eventReadWatch(){
    int hour, minutes;
    int *time_of_day;
    string hour_string, minute_string;

    time_of_day = SEASONS_D->GetMudTime();
    hour = time_of_day[0];
    minutes = time_of_day[1];

    if(hour > 12) hour -= 12;

    hour_string = cardinal(hour);
    switch(minutes){
        case 0 : minute_string ="整"; break;
        case 1 : minute_string = hour_string;hour_string ="过一分"; break;
        case 2 : minute_string = hour_string;hour_string ="过两分"; break;
        case 3 : minute_string = hour_string;hour_string ="过三分"; break;
        case 4 : minute_string = hour_string;hour_string ="过四分"; break;
        case 5 : minute_string = hour_string;hour_string ="过五分"; break;
        case 6 : minute_string = hour_string;hour_string ="过六分"; break;
        case 7 : minute_string = hour_string;hour_string ="过七分"; break;
        case 8 : minute_string = hour_string;hour_string ="过八分"; break;
        case 9 : minute_string = hour_string;hour_string ="过九分"; break;
        case 10 : minute_string = hour_string;hour_string ="过十分"; break;
        case 15 : minute_string = hour_string;hour_string ="过一刻"; break;
        case 45 : minute_string = cardinal(hour+1);hour_string ="差一刻"; break;
        case 50 : minute_string = cardinal(hour+1);;hour_string ="差十分"; break;
        case 55 : minute_string = cardinal(hour+1);hour_string ="差五分"; break;
        default : minute_string = cardinal(minutes);break;
    }

    if(minute_string == "thirteen") minute_string = "一";

    write("根据怀表显示，现在是"+hour_string+" "+minute_string+"。");

    return 1;
}
