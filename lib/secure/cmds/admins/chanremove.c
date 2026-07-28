// This command is only useful if you own an intermud channel

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string chan) {

    if(!archp(previous_object())) return 0;
    if( !chan || chan == "") {
        return "什么？";
    }
    if(member_array(chan,INTERMUD_D->GetChannels()) == -1)
        return "没有这个频道。";

    else INTERMUD_D->eventWrite( ({ "channel-remove", 5, mud_name(), 
                this_player()->GetKeyName(), INTERMUD_D->GetNameserver(), 
                0, chan }) );

    load_object("/secure/cmds/creators/update")->cmd("/daemon/intermud");

    write("频道移除请求已发送。");

    return 1;
}

string GetHelp(){
    return ("语法: chanremove <频道名>\n\n"
            "向跨MUD路由器提交请求，移除指定的频道。"
            "如果你不拥有该频道，请求将不会被处理。\n"
            "另见: chanban, chanunban, chancreate");
}
