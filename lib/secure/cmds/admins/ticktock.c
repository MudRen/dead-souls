#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(mixed args) {
    int *mudtime;
    int integer, hours, minutes, ret;
    string meridiem = " am";
    string nulle = "";

    if(!archp(previous_object())) return 0;
    if(!args) args = 0;
    if(stringp(args)){
        if(sscanf(args,"%d",integer) != 1) return "失败。";
        args = integer;
    }
    //tc("pre: "+SEASONS_D->GetCurrentTime());
    //tc("pre: "+identify(SEASONS_D->GetMudTime()));
    if(args != 0 || SEASONS_D->GetTickTock()){
        ret = SEASONS_D->eventTickTock(args);
    }
    //tc("post: "+SEASONS_D->GetCurrentTime());
    //tc("post: "+identify(SEASONS_D->GetMudTime()));

    mudtime = SEASONS_D->GetMudTime();
    hours = mudtime[0];
    minutes = mudtime[1];

    //tod = SEASONS_D->GetTimeOfDay();

    if(hours >= 12  && hours != 24) {
        if(hours != 12) hours -= 12;
        meridiem = " pm";
    }

    if(!hours || hours == 0) hours = 12;

    if(minutes < 10) nulle = "0";

    write("MUD中的时间是 "+hours+":"+nulle+minutes+meridiem+"。"); 

    return 1;

}

string GetHelp(){
    return ("语法: ticktock <秒数>\n\n"
            "将游戏内MUD时间改变指定的秒数。这在测试环境光线"
            "和可变房间描述时，用于将夜晚变为白天或反之。"
            "时间偏移在重启后不会保留。");
}
