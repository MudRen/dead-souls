#include <lib.h>
#include <cfg.h>

inherit LIB_DAEMON;

string *zones_cfg = explode((read_file(CFG_TIMEZONES)|| ""), "\n");

mixed cmd(string args) {
    string tz = this_player()->GetProperty("timezone");
    if(!tz || tz == "NONE") tz = "未设置时区。";

    if(!args){
        write("你的时区是: "+tz);
        return 1;
    }
    args = upper_case(args);
    if(member_array(args, (zones_cfg + ({"NONE"}))) == -1){
        write("这是未知的时区。");
        return 1;
    }
    this_player()->SetProperty("timezone", args);
    write("你的时区已设置为: "+args);
    return 1;
}

string GetHelp(){
    return ("用法: timezone [时区 | none]\n\n"
            "不带参数时，timezone 将显示你当前的时区。"
            "如果提供mud已知的有效时区，它将尝试将你的个人时区设置为该时区。"
            "\n参考: env");
}
