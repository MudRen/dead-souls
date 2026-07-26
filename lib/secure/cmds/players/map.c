#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string ret;
    int i = atoi(args);
    if(!i) i = 6;
    if(!creatorp(this_player())) i = 3;
    if(i <= 30 && !archp(this_player())) i = 29;
    ret = MAP_D->GetMap(environment(this_player()), i, 1);
    write(ret);
    return 1; 
}

string GetHelp(){
    return ("命令格式：map\n\n"
            "显示你当前位置的简单地图。");
}
