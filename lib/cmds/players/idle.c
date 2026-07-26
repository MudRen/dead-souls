/*  /cmds/players/idle
 *  Simple command which displays named player's idle time
 *  Recreated by Blitz@Dead Souls 960108
 */

mixed cmd(string args) {
    int x;
    object who;

    if( !sizeof(args) ) return 1;
    args = convert_name(args);
    who = find_player(args);
    if( !who || who->GetInvis() )
        return "找不到该玩家。";
    if( !interactive(who) )
        return who->GetName() + " 已断开连接。";
    x = query_idle(who);
    if( x > 4 ) {
        this_player()->eventPrint(who->GetName()+" 已发呆 "+time_elapsed(x)+"。");
    }
    else this_player()->eventPrint(who->GetName() + " 没有发呆。");
    return 1;
}

string GetHelp(string str) {
    return "用法: idle [用户]\n\n"
        "显示指定用户的发呆时间。用户的\"发呆时间\"是该用户\n"
        "最后一次向MUD发送输入以来的时间。\n"
        "如果不提供参数，此命令不执行任何操作。这允许你\n"
        "向mud发送命令以保持连接活跃而不产生活动。\n"
        "参考: keepalive, env";
}
