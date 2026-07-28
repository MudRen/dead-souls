#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object ob;
    args = lower_case(args);
    if(!user_exists(args)) return capitalize(args) + " 不是 " +
        mud_name() + " 的成员。";
    WEB_SESSIONS_D->EndSession(args);
    if(!ob = find_player(args)){
        if(member_array(args, PLAYERS_D->GetPendingUnpauses()) != -1){
            PLAYERS_D->RemovePendingUnpause(args);
            write("已移除 "+capitalize(args)+" 的待处理解除暂停。");
        }
        if(PLAYERS_D->GetPlayerData(args, "Paused")){
            return capitalize(args) + " 已被暂停。";
        }
        if(member_array(args, PLAYERS_D->GetPendingPauses()) != -1){
            return capitalize(args) + " 已在等待暂停处理。";
        }
        PLAYERS_D->AddPendingPause(args);
        write(capitalize(args)+" 将在下次登录时被暂停。");
        return 1;
    }
    if(ob == this_player()){
        write("你不能暂停自己。");
        return 1;
    }
    if(ob->GetPlayerPaused()){
        write(capitalize(args) + " 已被暂停！");
        return 1;
    }
    write("你已暂停 "+capitalize(args)+"。");
    ob->SetPlayerPaused(1);
    ob->eventPrint("你已被暂停。在解除暂停之前所有命令将无法使用。");
    return 1;
}

string GetHelp(){
    return ("语法: pause <玩家名>\n\n"
            "使该玩家无法执行任何命令。用于立即停止问题行为。");
}
