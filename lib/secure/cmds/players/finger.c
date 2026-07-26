#include <daemons.h>
#include <lib.h>
#include <socket.h>
#include <message_class.h>

inherit LIB_DAEMON;

void remote_finger(object me, string target, string mud);

mixed cmd(string str) {
    string wer, wo;

    if(!str) return "你想finger谁？";

    if(!str) {
        string ret;

        ret = FINGER_D->GetFinger(0);
        if( !ret ) return "通用finger功能似乎出现了问题。";
        this_player()->eventPage(explode(ret, "\n"), MSG_SYSTEM);
        return 1;
    }
    else if(sscanf(str, "%s@%s", wer, wo))
        remote_finger(this_player(), (wer ? wer : ""), wo);
    else {
        string ret;

        ret = FINGER_D->GetFinger(convert_name(str));
        if( !ret ) return "finger " + capitalize(str) + " 失败了。";
        this_player()->eventPage(explode(ret, "\n"), MSG_SYSTEM);
    }
    return 1;
}

void remote_finger(object ob, string who, string mud) {
    // If/Else If/Else construct didn't work for some strange reason
    // when I tried to add the IMC2 finger, so i just split it up with a return;
    // Shadyman, 2006-Sept-14

    if ( mud = INTERMUD_D->GetMudName(mud) ) {
        SERVICES_D->eventSendFingerRequest(convert_name(who), mud);
        message("system", "远程finger请求已发送到 " + mud + "。", this_player());
        return;
    }

    if ( mud = IMC2_D->find_mud(mud) ) {
        IMC2_D->finger(who+"@"+mud, ob);
        message("system", "远程finger请求已通过IMC2网络发送到 " + mud + "。", this_player());
        return;
    }

    message("system", mud_name() + "在I3或IMC2网络上都没有找到该MUD。", this_player());
}

string GetHelp(){
    return "命令格式：finger [[玩家]@[MUD]]\n\n"
        "显示指定玩家的信息。如果没有指定MUD，"
        "则在本MUD中搜索该玩家的信息。"
        "如果指定了另一个MUD但没有指定玩家，"
        "可能会显示该MUD上玩家的一般信息。\n"
        "参见：mail, rwho, tell, users, who";
}
