// This command is only useful if you own an intermud channel

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string chan, mud;

    if(!archp(previous_object())) return 0;
    if( !args || args == "" || sscanf(args,"%s %s",chan,mud) != 2) {
        return "什么？";
    }
    mud = INTERMUD_D->GetMudName(mud);
    if(!mud) return "没有这个MUD。";

    if(member_array(chan,INTERMUD_D->GetChannels()) == -1)
        return "没有这个频道。";

    else INTERMUD_D->eventWrite( ({ "channel-admin", 5, mud_name(), 
                this_player()->GetKeyName(), INTERMUD_D->GetNameserver(), 
                0, chan, ({}), ({ mud }) }) );

    write("已从 "+chan+" 解封 "+mud+" 的请求已发送。");

    return 1;
}

string GetHelp(){
    return ("语法: chanunban <频道名> <MUD名>\n\n"
            "向跨MUD路由器提交请求，将你拥有的频道中解封指定的MUD。"
            "如果你不拥有指定的频道，路由器将不会处理你的请求。"
            "请使用频道的\"真实\"名称，而不是本地昵称，"
            "例如 imud_code 而不是 intercre。\n"
            "示例: chanunban imud_gossip nanvaent\n"
            "另见: chanban, chancreate, chanremove");
}
