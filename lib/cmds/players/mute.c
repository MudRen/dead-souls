#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string which, type;
    string *validtypes = ({ "remote", "local", "all" });
    if( !sizeof(str) )
        return "用法: mute <on 或 off> [remote 或 local]";
    str = lower_case(str);
    sscanf(str,"%s %s",which, type);
    if(!type) type = "all";
    else str = which;
    if( str != "on" && str != "off" )
        return "你只能将 mute 设置为 'on' 或 'off'。";
    if( member_array(type, validtypes) == -1 )
        return "有效的 mute 类型有: remote, local, all。";
    this_player()->SetMuted(type, (str == "on"));
    message("system",
            "静音模式已为 "+type+" 频道"+str+"。",
            this_player() );
    return 1;
}

string GetHelp() {
    return ("用法: mute on [ remote | local ]\n"
            "        mute off [ remote | local ]\n\n"
            "此命令允许你屏蔽或收听频道消息。\n"
            "你可以用 mute on 静音所有频道\n"
            "你可以用 mute remote on 仅静音跨mud频道\n"
            "参考: gag, env");
}
