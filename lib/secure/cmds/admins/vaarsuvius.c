#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object tp = this_player();
    string tmpfile;
    string ret = "";
    int massacre, survivors = 0;
    object *obs;

    if(!tp || !archp(tp)) return "不行。";

    if(args) args = replace_string(args,"\"","");

    if(!args) return "试试: help vaarsuvius";

    else obs = findobs(args);

    if(!massacre = sizeof(obs)) {
        write("未找到此类对象。");
        return 1;
    }

    foreach(object ob in obs){
        ob->eventDestruct();
        if(ob) destruct(ob);
        if(ob){
            survivors++;
            write(identify(ob)+" 在清除中幸存。");
        }
    }
    if(!survivors){
        write("全部 "+massacre+" 个对象已销毁。");
        return 1;
    }
    write("在 "+massacre+" 个目标中，"+survivors+" 个在清除中幸存。");
    return 1;
}

string GetHelp(){
    return ("语法: vaarsuvius <对象>\n\n"
            "销毁找到的所有指定对象。\n"
            "另见: zap, dest, destfile");
}
