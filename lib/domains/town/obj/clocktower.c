#include <lib.h>
#include <daemons.h>

inherit LIB_ITEM;

int eventReadClock();

protected void create(){
    item::create();
    SetKeyName("钟楼");
    SetId( ({"great clock tower rising majestically into the sky", "great clock of the town", "clock", "tower", "structure", "architecture", "clocktower"}) );
    SetAdjectives( ({"large", "great", "majestic", "impressive", "proud"}) );
    SetShort("一座雄伟高耸入云的大钟楼");
    SetLong("这是一座大钟楼，雄伟地高耸入云。大约四十英尺高的地方你可以看到城镇的大钟，可以用来了解当地时间。其建筑的精致细节令人印象深刻，毫无疑问这座伟大的建筑是这个小镇的骄傲。");
    SetMass(1000000);
    SetBaseCost("silver",40);
    SetDefaultRead( (: eventReadClock :) );
}

void init(){
    ::init();
}

mixed CanGet(object ob) { return "这是一座钟楼，无法拾取。";}

int eventReadClock(){
    int hour, minutes;
    int *time_of_day;
    string hour_string, minute_string;
    time_of_day = SEASONS_D->GetMudTime();
    hour = time_of_day[0];
    minutes = time_of_day[1];

    if(hour > 12) hour -= 12;
    
    switch(hour){
        case 0: hour_string = "十二"; break;
        case 1: hour_string = "一"; break;
        case 2: hour_string = "二"; break;
        case 3: hour_string = "三"; break;
        case 4: hour_string = "四"; break;
        case 5: hour_string = "五"; break;
        case 6: hour_string = "六"; break;
        case 7: hour_string = "七"; break;
        case 8: hour_string = "八"; break;
        case 9: hour_string = "九"; break;
        case 10: hour_string = "十"; break;
        case 11: hour_string = "十一"; break;
        case 12: hour_string = "十二"; break;
    }
    
    switch(minutes){
        case 0 : minute_string ="整"; break;
        case 1 : minute_string = "一分"; break;
        case 2 : minute_string = "二分"; break;
        case 3 : minute_string = "三分"; break;
        case 4 : minute_string = "四分"; break;
        case 5 : minute_string = "五分"; break;
        case 6 : minute_string = "六分"; break;
        case 7 : minute_string = "七分"; break;
        case 8 : minute_string = "八分"; break;
        case 9 : minute_string = "九分"; break;
        case 10 : minute_string = "十分"; break;
        case 11 : minute_string = "十一分"; break;
        case 12 : minute_string = "十二分"; break;
        case 13 : minute_string = "十三分"; break;
        case 14 : minute_string = "十四分"; break;
        case 15 : minute_string = "十五分"; break;
        case 16 : minute_string = "十六分"; break;
        case 17 : minute_string = "十七分"; break;
        case 18 : minute_string = "十八分"; break;
        case 19 : minute_string = "十九分"; break;
        case 20 : minute_string = "二十分"; break;
        case 21 : minute_string = "二十一分"; break;
        case 22 : minute_string = "二十二分"; break;
        case 23 : minute_string = "二十三分"; break;
        case 24 : minute_string = "二十四分"; break;
        case 25 : minute_string = "二十五分"; break;
        case 26 : minute_string = "二十六分"; break;
        case 27 : minute_string = "二十七分"; break;
        case 28 : minute_string = "二十八分"; break;
        case 29 : minute_string = "二十九分"; break;
        case 30 : minute_string = "三十分"; break;
        case 31 : minute_string = "三十一分"; break;
        case 32 : minute_string = "三十二分"; break;
        case 33 : minute_string = "三十三分"; break;
        case 34 : minute_string = "三十四分"; break;
        case 35 : minute_string = "三十五分"; break;
        case 36 : minute_string = "三十六分"; break;
        case 37 : minute_string = "三十七分"; break;
        case 38 : minute_string = "三十八分"; break;
        case 39 : minute_string = "三十九分"; break;
        case 40 : minute_string = "四十分"; break;
        case 41 : minute_string = "四十一分"; break;
        case 42 : minute_string = "四十二分"; break;
        case 43 : minute_string = "四十三分"; break;
        case 44 : minute_string = "四十四分"; break;
        case 45 : minute_string = "四十五分"; break;
        case 46 : minute_string = "四十六分"; break;
        case 47 : minute_string = "四十七分"; break;
        case 48 : minute_string = "四十八分"; break;
        case 49 : minute_string = "四十九分"; break;
        case 50 : minute_string = "五十分"; break;
        case 51 : minute_string = "五十一分"; break;
        case 52 : minute_string = "五十二分"; break;
        case 53 : minute_string = "五十三分"; break;
        case 54 : minute_string = "五十四分"; break;
        case 55 : minute_string = "五十五分"; break;
        case 56 : minute_string = "五十六分"; break;
        case 57 : minute_string = "五十七分"; break;
        case 58 : minute_string = "五十八分"; break;
        case 59 : minute_string = "五十九分"; break;
    }

    write("根据钟楼的时钟，现在是"+hour_string+"点"+minute_string+"。");

    return 1;
}
