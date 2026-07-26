/*    /cmds/player/mudlist.c
 *    from the Dead Souls LPC Library
 *    gives information about muds
 *    created by Descartes of Borg 950623
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    mixed *info;
    string *list;
    mapping borg;
    string mud, tempy;
    int all = 0;

    if(sizeof(str) && sizeof(tempy = INTERMUD_D->GetMudName(str) )) str = tempy;

    //imc2 mudlist
    if(sizeof(str) && str[0..3] == "imc2") {
        IMC2_D->mudlist(this_player());
        return 1;
    }

    if( str && str != "" ) {
        mapping tmp;
        string opt, tmpstr;

        tmp = INTERMUD_D->GetMudList();
        if( str[0] != '-' ) str = "-n " + str;
        opt = str[1..1];
        str = str[3..];
        borg = ([]);
        foreach(mud, info in tmp) {
            int x, y, z;

            switch(opt) {
                case "a":
                    all = 1;
                    break;
                case "m":
                    x = 5;
                    break;
                case "d":
                    x = 7;
                    break;
                case "n":
                    x = 0;
                    break;
            }
            tmpstr = (x ? info[x] : mud);
            z = strlen(str);
            y = strlen(tmpstr);


            if( lower_case(str) == lower_case(tmpstr) ) {
                borg = ([ mud : info ]);
                break;
            }

            else if( y > z &&
                    lower_case(tmpstr[0..z-1]) == lower_case(str) && info[0] == -1 )
                borg[mud] = info;
        }
    }
    else {
        borg = ([ ]);
        foreach( mud, info in INTERMUD_D->GetMudList() )
            if( all == 1 || info[0] == -1 ) borg[mud] = info;
    }
    if( !sizeof(borg) ) {
        if(this_player()) message("system", "没有MUD匹配你的查询。", this_player());
        return 1;
    }
    else if( sizeof(borg) == 1 ) {
        string msg, svc;
        int val, comma = 0;

        mud = keys(borg)[0];
        msg = "\n%^GREEN%^" + mud + "%^RESET%^ 的详细信息:\n";
        msg += sprintf("MUD类型: %:-6s 服务器: %:-20s 库: %s\n",
                borg[mud][8], borg[mud][7], borg[mud][5]);
        msg += "状态: " + borg[mud][9] + "\n管理员邮箱: " +
            borg[mud][10] + "\n";
        msg += "服务: ";
        foreach(svc, val in borg[mud][11]) {
            if( val == 1 ) {
                if( comma ) msg += ", " + svc;
                else {
                    msg += svc;
                    comma = 1;
                }
            }
        }
        msg += "\n主机: " + borg[mud][1] + "\n";
        msg += "Telnet端口: " + borg[mud][2] + "\n";
        if( borg[mud][11]["amcp"] )
            msg += "AMCP版本: " + borg[mud][11]["amcp"] + "\n";
        if( borg[mud][11]["http"] )
            msg += "HTTP端口 (万维网): " + borg[mud][11]["http"]+"\n";
        if( borg[mud][11]["ftp"] )
            msg += "FTP端口 (文件传输): " + borg[mud][11]["ftp"] + "\n";
        if( borg[mud][11]["rcp"] )
            msg += "RCP端口 (远程创造者): " + borg[mud][11]["rcp"] + "\n";
        if(this_player()) message("info", msg, this_player());
        return 1;
    }
    list = ({});
    foreach(mud, info in borg)
        list += ({ sprintf("%:-15s %:-6s %:-15s %:-18s %s %d",
                    replace_string(mud,"%^","%%^^"), info[8], info[7], info[5], info[1], info[2]) });
    list = sort_array(list, 1);
    list = ({ replace_string(mud_name(),"%^","%%^^") + " 识别到 " + consolidate(sizeof(borg), "a mud")+
            " 匹配你的查询: ", "" }) + list;
    if(this_player()) this_player()->eventPage(list);
    if(this_player()) return 1;
    else return implode(list,"\n");
}

int alphabet(string a, string b) {
    if((a = lower_case(a)) == (b = lower_case(b))) return 0;
    else if(a > b) return 1;
    else return -1;
}

string GetHelp() {
    return ("用法: mudlist [-d] [-m] [-n] [参数]\n"
            "        <mudlist imc2>\n\n"
            "不带参数时，它会列出所有可以通过tell、mail、finger、rwho"
            "和其他跨mud服务进行通信的mud的完整列表。"
            "带参数时，<mudlist> 需要且仅需要一个选项，必须是以下之一：\n"
            "\t-d [驱动]: 仅列出使用指定驱动的mud\n"
            "\t-m [mudlib]: 仅列出使用指定mudlib的mud\n"
            "\t-n [mud名称]: 仅列出指定名称的mud\n\n"
            "注意参数不必完整，例如：\n"
            "\t mudlist -n idea\n"
            "将列出 IdeaExchange 以及名称以 \"idea\" 开头的任何其他mud。\n"
            "参考: finger, mail, rwho, tell");
}
