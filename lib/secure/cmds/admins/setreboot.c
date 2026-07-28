#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    int x;

    if( !(master()->valid_apply(({ "ASSIST" }))) ){
        return 0;
    }

    if(!str || str == "" || !sscanf(str, "%d", x)){
        this_object()->help();
    }
    x = EVENTS_D->SetRebootInterval(x);
    message("info", "重启间隔已设置为 "+x+" 小时。", this_player());
    return 1;
}

string GetHelp(){
    return ("语法: setreboot <间隔时间>\n\n"
            "设置MUD自动重启的间隔时间。间隔时间以小时为单位。");
}
