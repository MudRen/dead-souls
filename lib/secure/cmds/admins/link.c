/*    /secure/cmds/admins/link.c
 *    from the Dead Souls Mud Library
 *    link SECONDARY to PRIMARY
 *    link PLAYER
 *    link
 *    created by Descartes of Borg 951216
 */

#include <lib.h>
#include <link.h>
#include <daemons.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    mixed tmp;
    string primary, secondary;

    if( !archp(previous_object()) ) return 0;

    // If no arguments are specified, dump all links. 
    if( !args || args == "" ) {
        mapping links;
        string formatString;
        int screenSize = ((int *)this_player()->GetScreen())[0];
        int playerSize = ((screenSize * 4) / 16) -1;
        int emailSize = ((screenSize * 6) / 16) - 1;
        int lastOnSize = ((screenSize * 6) / 16) - 1;

        if(playerSize < 14) playerSize = 14;
        if(emailSize < 25) emailSize = 25;
        if(lastOnSize < 25) lastOnSize = 25;

        formatString = "%:-" + playerSize + "s %:-" + emailSize
            + "s %:-" + lastOnSize + "s";

        tmp = ({ center("%^CYAN%^  " + mud_name()
                    + " 已批准的角色关联%^YELLOW%^", screenSize) });

        tmp += ({ sprintf(formatString, "玩家", "邮箱", "最后登录%^RESET%^") });

        links = CHARACTER_D->GetLinks();
        foreach(string p in sort_array(keys(links), 1)) {   
            class char_link l;
            int maxi;

            l = links[p];
            if( !(maxi = sizeof(l->Secondaries)) ) continue;
            tmp += ({ sprintf(formatString, capitalize(p), l->Email,
                        ((l->LastOnWith == p) ? ctime(l->LastOnDate) : "未知")) });
            foreach(string pl in l->Secondaries)
                tmp += ({ sprintf(formatString, "  " + capitalize(pl), "",
                            ((l->LastOnWith == pl) ? ctime(l->LastOnDate) : "未知")) });
        }
        this_player(1)->eventPage(tmp, MSG_SYSTEM);
        return 1;
    }

    // Or, link a secondary to a primary.
    else if( sscanf(args, "%s to %s", secondary, primary) == 2 ) {
        this_player(1)->eventPrint("该玩家的邮箱: ", MSG_PROMPT);
        input_to(function(string email, string primary, string secondary) {
                mixed tmp;

                if( !email || email == "" ) {
                this_player(1)->eventPrint("已中止。", MSG_SYSTEM);
                return;
                }
                tmp = CHARACTER_D->eventLink(primary, secondary, email);
                if( !tmp ) this_player(1)->eventPrint("失败。", MSG_SYSTEM);
                else if( tmp == 1) this_player(1)->eventPrint("已关联。", MSG_SYSTEM);
                else this_player(1)->eventPrint(tmp, MSG_SYSTEM);
                }, primary, secondary);
        return 1;
    }

    // Otherwise, get link information on a specific player.
    else {
        mapping mp;
        string str;

        mp = CHARACTER_D->GetLink(convert_name(args));
        if( !mp ) this_player()->eventPrint(capitalize(args) + " 没有"
                "已记录的关联。", MSG_SYSTEM);
        else {
            str = "主角色: " + capitalize(mp["primary"]) + "\n";
            str += "最后于 " + ctime(mp["last on"]) + " 使用 " +
                capitalize(mp["last char"]) + " 登录\n";
            str += "关联角色: " + implode(mp["secondaries"], ",");
            this_player()->eventPrint(str, MSG_SYSTEM);
        }
        return 1;
    }
}

string GetHelp(){
    return ("语法: link <关联角色> to <主角色>\n"
            "        link <玩家名>\n"
            "        link\n\n"
            "第一种形式允许你将两个角色标记为由同一个真人控制。"
            "它创建一个关系，其中一个角色被视为主要角色，另一个为关联角色。"
            "如果一个或多个角色已有关联关系，这将修改这些关系，"
            "并以你指定的主角色创建新的关联。例如，如果两个角色"
            "都已被设为主要关联，你用此命令指定为主要角色的那个"
            "将成为这些角色的唯一主要关联，而关联角色及其关联角色"
            "都将成为其关联角色。\n\n"
            "如果只传入玩家名作为参数，此命令将显示该玩家的关联信息。\n\n"
            "如果不带参数，此命令将列出所有已知的关联。\n\n"
            "另见: finger, unlink");
}
