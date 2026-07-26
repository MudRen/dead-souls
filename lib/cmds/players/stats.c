/*    /cmds/player/stats.c
 *    from the Dead Souls LPC Library 
 *    command to view stats
 *    created by Descartes of Borg 950409
 */

#include <lib.h>

inherit LIB_DAEMON;
object who;

mixed cmd(string args) {
    string *stats;
    string ret, tmp;
    int i, x, y;
    who = 0;

    if(args){
        if(!creatorp(this_player())){
            write("用法: help stats");
            return 1;
        }
        if(args == "me" || args == "myself") who = this_player();
        if(!who) who = find_player(lower_case(args));
        if(!who){
            object *creatures = get_livings(environment(this_player()));
            creatures = filter(creatures,
                    (: answers_to(lower_case($(args)), $1) :));
            if(sizeof(creatures)) who = creatures[0];
        }
        if(!who){
            write("找不到该生物。");
            return 1;
        }
    }

    else who = this_player();

    ret = who->GetShort() + "，等级 " +
        who->GetLevel();
    if( (tmp = who->GetClass()) )
        ret += " " + capitalize(tmp);
    else ret += " Drifter";
    ret += " (" + who->GetRace() + ")\n";
    stats = map(sort_array(who->GetStats(), 1),
            (: sprintf("%:-20s: %:-3d", $1, 
                       who->GetStatLevel($1)) :));
    i = sizeof(stats);
    while(i--) if( (y = strlen(stats[i])) > x ) x = y;
    x = (this_player()->GetScreen())[0]/(x+2);
    ret += format_page2(stats, x);
    message("system", ret, this_player());
    return 1;
}

string GetHelp() {
    if(creatorp(this_player())){
        return ("用法: stats [玩家]\n\n"
                "列出指定玩家的属性及其等级。不带参数时默认显示自己的属性。\n"
                "参考: stat, status, score");
    }
    else {
        return ("用法: stats\n\n"
                "列出你所有的属性及其等级。\n"
                "参考: stat, status, score");
    }
}
