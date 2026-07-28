// This command is only useful if you own an intermud channel

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string chan;
    int mode = 0;

    if(!archp(previous_object())) return 0;
    write("此命令用于创建跨MUD-3频道。" +
            "你几乎肯定不需要使用它。如果你100%确定你知道" +
            "自己在做什么，并且确实需要创建一个跨MUD-3频道，" +
            "请编辑此命令以移除此警告及其后的 return 语句。");
    return 1;
    if( !args || args == "") return "什么？";
    if(sscanf(args,"%s %d",chan,mode) != 2) chan = args;
    if(mode > 2 || mode < 0) return "无效的模式。";

    else INTERMUD_D->eventWrite( ({ "channel-add", 5, mud_name(), 
                this_player()->GetKeyName(), INTERMUD_D->GetNameserver(), 
                0, chan, mode }) );

    load_object("/secure/cmds/creators/update")->cmd("/daemon/intermud");

    write("频道创建请求已发送。");
    return 1;
}

string GetHelp(){
    return ("语法: chancreate <名称> [0 | 1 | 2]\n\n"
            "向跨MUD路由器提交请求，创建你指定名称和模式的跨MUD频道。"
            "如果同名的跨MUD频道已存在，你的请求将不会被处理。"
            "否则在几分钟的更新和广播后，你的新频道应该就可用了。"
            "模式指示是否为仅邀请频道。例如:\nchancreate macrame 1\n"
            "将创建一个名为 macrame 的频道，在你明确允许之前"
            "没有MUD可以使用它。另一方面，"
            "\nchancreate dramallamas\n 将创建一个任何MUD都可以加入的频道，"
            "直到你明确用 chanban 封禁它们。模式2即\"过滤\"模式，"
            "是一个高级主题，留给读者自行研究。"
            "\n另见: chanban, chanunban, chanremove, "
            "http://www.intermud.org/specs/i3.html");
}
