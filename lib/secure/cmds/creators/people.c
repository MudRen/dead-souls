/*    /cmd *    from Dead Souls
 *    a listing of users for creators and ambassadors
 *    created by Descartes of Borg 940724
 */

#include <lib.h>
#include <localtime.h>
#include <dirs.h>
#include <daemons.h>

inherit LIB_DAEMON;

nosave private int *__SortFlags;

private string query_people_time();
private string calculateFormatString(int screenSize);
object *whom, *who, *display;
string *args;

string GetBaseName(object ob){
    string ret;
    if(ob) ret = capitalize(cleaned_end(base_name(ob)));
    if(!ret && ob) ret = ob->GetCapName();
    if(!ret) ret = "";
    return ret;
}

mixed room_env(object ob){
    string *riders;
    object env = environment(ob);
    if(!env) return 0;
    if(!living(env)) return env;
    if(arrayp(riders = env->GetRiders()) && member_array(ob, riders) != -1 &&
            environment(env)) env = environment(env);
    return env;
}

int cmd(string str) {
    string msg, tmp1, tmp2;
    int i, maxi, aflag, bflag, cflag, eflag, gflag, hflag, lflag, mflag;
    int nflag, pflag, rflag, sflag, uflag;
    int screenSize;
    string formatString;
    string bar;

    whom = ({});

    if(!str || str == "" || strlen(str) == 1 || str[0] != '-') args = ({});
    else args = explode(str[1..strlen(str)-1], "");
    i = sizeof(args);
    while(i--) {
        switch(args[i]) {
            case "a": aflag = 1; break; /* list arches */
            case "b": bflag = 1; break; /* list ambassadors */
            case "c": cflag = 1; break; /* list creators */
            case "e": eflag = 1; break; /* sort by race */
            case "g": gflag = 1; break; /* sort by age */
            case "h": hflag = 1; break; /* list high mortals */
            case "l": lflag = 1; break; /* sort by level */
            case "m": mflag = 1; break; /* page through eventPage */
            case "n": nflag = 1; break; /* list newbies */
            case "p": pflag = 1; break; /* list regular mortals */
            case "r": rflag = 1; break; /* sort by realm location */
            case "s": sflag = 1; break; /* sort by class */
            case "u": uflag = 1; break; /* list undead */
        }
    }
    who = filter(users(), "filter_invis", this_object());
    foreach(object real_person in who){
        if(sizeof(base_name(real_person))) whom += ({ real_person });
    }

    who = whom;

    if(!aflag && !bflag && !cflag && !hflag && !nflag && !pflag && !uflag)
        display = who;
    else {
        display = ({});
        if(aflag) display += filter(who, "filter_arches", this_object());
        if(bflag) display += filter(who, "filter_ambass", this_object());
        if(cflag) display += filter(who, "filter_cres", this_object());
        if(hflag) display += filter(who, "filter_hms", this_object());
        if(nflag) display += filter(who, "filter_newbie", this_object());
        if(pflag) display += filter(who, "filter_mortal", this_object());
        if(uflag) display += filter(who, "filter_undead", this_object());
        display = distinct_array(display);
    }
    if(!eflag && !gflag && !lflag && !rflag && !sflag)
        maxi = sizeof(display=sort_array(display,"general_sort",this_object()));
    else {
        __SortFlags = ({ eflag, gflag, lflag, rflag, sflag });
        maxi = sizeof(display = sort_array(display,"special_sort",this_object()));
    }
    screenSize = ((int*)this_player()->GetScreen())[0];
    formatString = calculateFormatString(screenSize);
    bar = "--------------------------------------------------------------------------";
    for(i = 75; i < screenSize; i++) bar += "-";
    bar += "\n";
    msg = bar;
    tmp1 = " " + maxi + " 人（当前排序） ";
    tmp2 = query_people_time() + " ";
    i = sizeof(tmp1) + sizeof(tmp2);
    msg += tmp1;
    for(i = sizeof(tmp1) + sizeof(tmp2) + 1; i < screenSize; i++) msg += " ";
    msg += tmp2 + "\n";
    msg += bar;
    msg += implode(map_array(display, "map_info", this_object(), formatString), "\n") + "\n";
    msg += bar;
    msg += center(mud_name(), screenSize - 1);
    if(!check_string_length()) mflag = 1;
    if(!mflag && check_string_length(msg)) this_player()->eventPrint(msg);
    else print_long_string(this_player(),msg);
    return 1;
}

protected int filter_invis(object ob) {
    if(!ob || !sizeof(base_name(ob))) return 0;
    if(!(ob->GetKeyName())) return 0;
    if(!(ob->GetInvis(this_player()))) return 1;
    if(archp(this_player())) return 1;
    if(archp(ob)) return 0;
    return 1;
}

protected int filter_arches(object ob) { return archp(ob); }

protected int filter_ambass(object ob) { return ambassadorp(ob); }

protected int filter_cres(object ob) { return (creatorp(ob) && !archp(ob)); }

protected int filter_hms(object ob) { return high_mortalp(ob); }

protected int filter_newbie(object ob) {
    return (!creatorp(ob) && !ambassadorp(ob) && (MAX_NEWBIE_LEVEL >=
                ob->GetLevel()));
}

protected int filter_mortal(object ob) {
    if(creatorp(ob) || high_mortalp(ob) || ambassadorp(ob)) return 0;
    if(ob->GetLevel() <= MAX_NEWBIE_LEVEL) return 0;
    return 1;
}

protected int filter_undead(object ob) { return ob->query_ghost(); }

nosave int general_sort(object alpha, object beta) {
    int x, y;

    if(archp(alpha)) {
        if(!archp(beta)) return -1;
        else return strcmp(GetBaseName(alpha),
                GetBaseName(beta));
    }
    else if(archp(beta)) return 1;
    if(creatorp(alpha)) {
        if(!creatorp(beta)) return -1;
        else return strcmp(GetBaseName(alpha),
                GetBaseName(beta));
    }
    else if(creatorp(beta)) return 1;
    if(ambassadorp(alpha)) {
        if(!ambassadorp(beta)) return -1;
        else return strcmp(GetBaseName(alpha),
                GetBaseName(beta));
    }
    else if(ambassadorp(beta)) return 1;
    if((x = alpha->GetLevel()) > (y = beta->GetLevel()))
        return -1;
    else if(x < y) return 1;
    else return strcmp(GetBaseName(alpha),
            GetBaseName(beta));
}

nosave int special_sort(object alpha, object beta) {
    string a, b;
    int x, y;

    if(__SortFlags[4]) {
        if((a=alpha->query_class())!=(b=beta->query_class())) {
            if(!a) a = "zzzz";
            if(!b) b= "zzzz";
            return strcmp(a, b);
        }
    }
    if(__SortFlags[0]) {
        if((a=alpha->query_race()) != (b=beta->query_race())) {
            if(!a) a = "zzzz";
            if(!b) b = "zzzz";
            return strcmp(a, b);
        }
    }
    if(__SortFlags[3]) {
        if((a = file_name(room_env(alpha))) !=
                (b = file_name(room_env(beta)))) return strcmp(a, b);
    }
    if(__SortFlags[2]) {
        if((x = alpha->GetLevel()) != (y=beta->GetLevel())) {
            if(x > y) return -1;
            else return 1;
        }
    }
    if(__SortFlags[1]) {
        if((x = alpha->GetAge()) != (y = beta->GetAge())) {
            if(x > y) return -1;
            else return 1;
        }
    }
    return 0;
}

private string calculateFormatString(int screenSize) {
    int nomSize = (((screenSize - 21) * 12) / 54);
    int ipSize = (((screenSize - 21) * 18) / 54);
    int envSize = (((screenSize - 21) * 24) / 54);

    if(nomSize < 12) nomSize = 12;
    if(ipSize < 18) ipSize = 18;
    if(envSize < 24) envSize = 24;

    return "%:-5s %:-2s %:-" + nomSize + "s %:-" + ipSize
        + "s %:-5s %:-3s %:-" + envSize + "s";
}

nosave string map_info(object ob, string formatString) {
    string age, nom, blk, lev, ip, env, idle;
    int x;

    x = ob->GetAge();
    if(x > 86400) age = sprintf("%:-2d D", x/86400);
    else if(x > 7200) age = sprintf("%:-2d h", x/3600);
    else age = sprintf("%:-2d m", x/60);
    nom = GetBaseName(ob);
    if(ob->GetInvis()) nom = "("+nom+")";
#ifndef __DSLIB__
    if(in_edit(ob) || in_input(ob)) nom = "["+nom+"]";
#else
    if(ob->GetCharmode()){
        if(in_edit(ob)) nom = "["+nom+"]";
    }
    else if(in_edit(ob) || in_input(ob)) nom = "["+nom+"]";
#endif
    if(creatorp(ob)) {
        if(ob->GetBlocked("all")) blk = "ACG";
        else {
            if(ob->GetBlocked("cre")) blk = " C";
            else blk = "  ";
            if(ob->GetBlocked("gossip")) blk += "G";
            else blk += " ";
        }
    }
    else blk = "   ";
    if(!(x = ob->GetLevel())) lev = "-";
    else lev = x+"";
    if((x = query_idle(ob)) < 60) idle = "";
    else if(x >= 3600) idle = sprintf("%:-3d h", x/3600);
    else idle = sprintf("%:-2d m", x/60);
    ip = query_ip_name(ob);
    if(ip == "0.0.0.0" || ip == "w.x.y.z") ip = "";
    if(!room_env(ob)) env = "无环境";
    else env = file_name(room_env(ob));
    if(!strsrch(env, REALMS_DIRS))
        env = "~" + env[strlen(REALMS_DIRS)+1..];
    else if(!strsrch(env, DOMAINS_DIRS))
        env = "^"+env[strlen(DOMAINS_DIRS)+1..strlen(env)-1];
    return sprintf(formatString, age, lev, nom, ip, idle, blk, env);
}

private string query_people_time() {
    string tzone;
    if(this_player()) tzone = this_player()->GetProperty("timezone");
    if(!tzone || !valid_timezone(tzone)) tzone = query_tz();
    return tzone + " 时间为: " + local_ctime(time(), tzone);
}

string GetHelp() {
    return ("语法: people [-abceghlmnprsu]\n\n"
            "列出 "+mud_name()+" 上的在线用户。输出按列排列，含义如下:\n"
            "    在 "+mud_name()+" 上的总时间\n"
            "    等级\n"
            "    名字\n"
            "    连接地址\n"
            "    空闲时间\n"
            "    屏蔽信息... A=全部, C=创造者, G=闲聊\n"
            "    当前环境文件名\n\n"
            "命令参数含义:\n"
            "    -a 列出所有大管理员\n"
            "    -b 列出所有大使\n"
            "    -c 列出所有非大管理员的创造者\n"
            "    -e 按种族排序\n"
            "    -g 按年龄排序\n"
            "    -h 列出所有高等凡人\n"
            "    -l 按等级排序\n"
            "    -m 通过分页器显示\n"
            "    -n 列出所有新手\n"
            "    -p 列出所有非新手非高等凡人\n"
            "    -r 按当前环境排序\n"
            "    -s 按职业排序\n"
            "    -u 列出所有亡灵\n\n"
            "在编辑器、邮件或公告中的用户会标记为 []。\n"
            "对你不可见的其他用户会标记为 ()。\n"
            "默认排序为大管理员、创造者、大使、等级。\n"
            "你可以进行多种排序，但不能更改优先级。\n"
            "排序优先级: 职业、种族、领域、等级、年龄。\n"
            "另见: who, users");
}
