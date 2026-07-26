/*    /cmds/player/rwho.c
 *    from the Dead Souls LPC Library
 *    Sends an Intermud 3 who request
 *    created by Descartes of Borg 950623
 *
 *    IMC2 support added by Shadyman 2006-Sep-12
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int CheckMud(string name){
    if(!(name = INTERMUD_D->GetMudName(name)) ) return 0;
    if(!INTERMUD_D->GetMudList()[name][0]) return 0;
    return 1;
}

mixed cmd(string str) {
    string tmp, s1, s2;
    string network = "i3";

    if( !str ) return "从哪里获取远程who列表？";

    if(grepp(str,"@")){
        if(sscanf(str,"%s@%s", s1, s2) < 2){
            write("名称格式不正确。仍然尝试...");
        }
        else str = s1;

        if(s2 && lower_case(s2) == "imc2"){
            network = "imc2";
            str = imc2_mud_name(s1);
        }
    }

    if ( network == "imc2" && find_object(IMC2_D) && (tmp = IMC2_D->find_mud(str)) ) {
        IMC2_D->who_out(capitalize(this_player()->GetKeyName()),tmp);
        message("system", "远程who查询已发送到 IMC2 网络上的 " + tmp + "。", this_player());
        return 1;
    } else if( CheckMud(str) ) {
        tmp = INTERMUD_D->GetMudName(str);
        SERVICES_D->eventSendWhoRequest(tmp);
        message("system", "远程who查询已发送到 I3 网络上的 " + tmp + "。", this_player());
        return 1;
    } else {
        return mud_name() + " 不知道这个地方，或者它目前不可用。";
        //Maybe do more processing here for bad spelling, etc?
    }
    return "糟糕，rwho 检查失败了。";
}

string GetHelp(){
    return ("用法: rwho <mud>\n\n"
            "从全球网络上的mud获取简要的who列表。\n"
            "who提供的信息因mud而异。\n"
            "默认情况下，此命令查询 i3 网络。你可以指定 IMC2\n"
            "使用以下语法: rwho mudname@imc2");
}
