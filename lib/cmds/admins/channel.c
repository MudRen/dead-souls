/*    /cmd *    from Dead Souls
 *    command to handle channel privs
 *    created by Descartes of Borg 940428
 */

#include <lib.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string opt, who, channel;
    object ob;

    if(!str) return 0;
    if(!archp(previous_object())) return 0;

    // Attempt to remove or add a players line rights.
    if(sscanf(str, "%s %s %s", opt, who, channel) == 3) {
        if(!(ob = find_player(lower_case(who))))
            return notify_fail("该玩家不在线。\n");
        if(opt == "remove") {
            if(member_array(channel, ob->GetChannels()) == -1) {
                this_player()->eventPrint(ob->GetName()
                        + " 目前没有订阅 " + channel + " 频道。");
                return 1;
            }
            ob->RestrictChannel(channel);
            this_player()->eventPrint("%^RED%^你已限制 " + ob->GetName()
                    + " 使用 " + channel + " 频道。%^RESET%^");
            ob->eventPrint("%^RED%^你已失去 " + channel
                    + " 频道的使用权限。%^RESET%^");
            return 1;
        }
        else if(opt == "add") {
            if(member_array(channel, ob->GetRestrictedChannels()) == -1) {
                message("system", ob->GetName() + " 目前没有被限制使用 "
                        + channel + " 频道。", this_player());
                return 1;
            }
            ob->UnrestrictChannel(channel);
            this_player()->eventPrint("%^RED%^你已解除 " + ob->GetName()
                    + " 对 " + channel + " 频道的限制。%^RESET%^");
            ob->eventPrint("%^RED%^你已恢复 " + channel
                    + " 频道的使用权限。%^RESET%^");
            return 1;
        }
    }
    // Otherwise, return restriction information, if it is requested.
    else if(str) {
        string *channels;
        string tmp;
        int size;

        if(!(ob = find_player(lower_case(str))))
            return notify_fail("该玩家不在线。\n");
        channels = ob->GetRestrictedChannels();
        size = sizeof(channels);
        tmp = ob->GetName() + " 目前被限制使用";
        if(size) tmp += "：" + implode(channels, "、");
        else tmp += "无";
        tmp += "频道。";
        this_player()->eventPrint(tmp);
        return 1;
    }
    else return 0;
}

string GetHelp() {
    return "Syntax: channel <add|remove> <player> <channel>\n"
        "        channel <player>\n\n"
        "Used to restrict a player from using a line, or to allow them back "
        "onto that line. You can also request a listing of a players currently "
        "restricted lines with this command.";
}
