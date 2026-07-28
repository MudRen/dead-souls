//      /bin/dev/_banish.c
//      from the Dead Souls Mudlib
//      prevents a name being used by a new player
//      created by Descartes of Borg ???

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    int substr = 0;

    if(!str || str == ""){
        write("语法: banish <字符串>");
        return 1;
    }

    if(grepp(str,"-s ")){
        str = replace_string(str,"-s ","");
        substr = 1;
    }
    if(!user_exists(str = lower_case(str))) {
        if(!substr){
            BANISH_D->banish_name(str);
            write(capitalize(str)+" 已被封禁。\n");
        }
        else {
            BANISH_D->set_illegal_substring(str);
            write("子字符串 \""+str+"\" 现在被禁止在名称中使用。");
        }
    }
    else {
        write("该名称的玩家已存在。\n");
        this_player()->eventPrint(FINGER_D->GetFinger(str));
    }
    return 1;
}

string GetHelp(){
    return ("语法: banish [-s] <名称 | 词语>\n\n"
            "保护名称不被新玩家使用。\n"
            "例如，如果你创建了一个名为 Cassandra 的怪物，为了\n"
            "避免玩家抱怨『我输入 kill cassandra 想杀那个邪恶的\n"
            "女巫，但 Cassandra 刚好走进来被我不小心杀了』这类问题。\n"
            "也用于防止玩家使用冒犯性的词语作为名称。\n"
            "-s 选项将参数设为要禁止的子字符串，例如:\n"
            "banish -s top\n"
            "将使创建名为 Carrottop 的角色成为不可能。"
           );
}
