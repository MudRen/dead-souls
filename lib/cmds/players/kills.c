#include <lib.h>

inherit LIB_DAEMON;

mapping kills = ([]);

mixed cmd(string args) {
    string *stats;
    string killfile, ret, tmp, name;
    int i, x, y;

    name = lower_case(this_player()->GetKeyName());
    killfile = "/save/kills/"+name[0..0]+"/"+name;
    if(!file_exists(killfile)) {
        write("你还没有任何击杀记录。");
        return 1;
    }
    kills = restore_variable(read_file(killfile));
    if(!sizeof(kills)){
        write("你从未伤害过任何生命。");
        return 1;
    }
    ret = "你是 " +this_player()->GetShort() + "，等级 " +
        this_player()->GetLevel();
    if( (tmp = this_player()->GetClass()) ) 
        ret += " " + capitalize(tmp);
    else ret += " 流浪者";
    ret += " (" + this_player()->GetRace() + ")\n";
    ret+= "你的胜利列表如下：\n\n";
    stats = map(keys(kills),
            (: sprintf("%:-20s: %:-1i", $1, 
                       kills[$1]) :));
    i = sizeof(stats);
    while(i--) if( (y = strlen(stats[i])) > x ) x = y;
    x = ((int *)this_player()->GetScreen())[0]/(x+2);
    ret += format_page(stats, x);
    message("system", ret, this_player());
    return 1;
}

string GetHelp() {
    return ("语法：kills\n\n"
            "显示你的胜利列表。");
}
