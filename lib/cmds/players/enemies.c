#include <lib.h>

inherit LIB_DAEMON;
string *foenames = ({});

mixed cmd(string str) {
    object *foes = ({});
    object ob;
    string ret;
    foenames = ({});
    if(sizeof(str) && !creatorp(this_player())){
        if(find_player(lower_case(str)) != this_player())
            return "你只能查看自己的敌人。";
    }
    if(!str) str = this_player()->GetKeyName();
    ob = find_player(lower_case(str));
    if(!ob) return "找不到该玩家。";
    foes = ob->GetEnemies();
    if(!sizeof(foes)){
        ret = "没有生物对 "+capitalize(str)+" 怀有敌意。";
    }
    else {
        ret = "以下生物对 "+capitalize(str)+" 怀有敌意: ";
        filter(foes, (: foenames += ({$1->GetShort()}) :) );
        ret += implode(foenames, ", ")+"。";
    }
    return ret;
}

string GetHelp() {
    return ("用法: enemies\n\n"
            "此命令报告你与谁关系不好。");
}

