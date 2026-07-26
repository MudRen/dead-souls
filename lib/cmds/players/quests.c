#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string ret;
    object dude;

    if(str && !creatorp(this_player()) ) {
        if(!find_player(str) || find_player(str) != this_player()){
            write("你只能查看自己的任务信息。");
            return 1;
        }
    }
    if(str && !find_player(str)){
        write("该玩家未登录。");
        return 1;
    }
    if(str) dude = find_player(str);
    else dude = this_player();
    if(!sizeof(dude->GetQuests())){
        if(dude == this_player()) write("你还没有完成任何任务。");
        else write(dude->GetName()+" 还没有完成任何任务。");
        return 1;
    }

    if(dude == this_player()) ret = "你已完成以下任务：\n";
    else ret = dude->GetName()+" 已完成以下任务：\n";

    ret += "----------------------------------------\n";

    foreach(string key, mapping val in dude->GetQuests()){
        ret += val["Description"] + "\n";
    }
    write(ret);
    return 1;
}

string GetHelp(){
    return ("用法: quests\n\n"
            "此命令列出你已完成的任务。");
}
