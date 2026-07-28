#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object ob;
    args = lower_case(args);
    if(!user_exists(args)) return capitalize(args) + " 不是 " +
        mud_name() + " 的成员。";
    if(!ob = find_player(args)){
        if(member_array(args, PLAYERS_D->GetPendingPauses()) != -1){
            PLAYERS_D->RemovePendingPause(args);
            write("已移除 "+capitalize(args)+" 的待处理暂停。");
        }
        if(!(PLAYERS_D->GetPlayerData(args, "Paused"))){
            return capitalize(args) + " 已处于未暂停状态。";
        }
        if(member_array(args, PLAYERS_D->GetPendingUnpauses()) != -1){
            return capitalize(args) + " 已在等待解除暂停处理。";
        }
        PLAYERS_D->AddPendingUnpause(args);
        write(capitalize(args)+" 将在下次登录时解除暂停。");
        return 1;
    }
    if(ob == this_player()){
        write("你不能解除自己的暂停。");
        return 1;
    }
    if(!(ob->GetPlayerPaused())){
        write(capitalize(args) + " 已处于未暂停状态！");
        return 1;
    }
    write("你已解除 "+capitalize(args)+" 的暂停。");
    ob->SetPlayerPaused(0);
    ob->eventPrint("你已被解除暂停。现在可以正常使用命令了。");
    return 1;
}

string GetHelp(){
    return ("语法: unpause <玩家名>\n\n"
            "使被暂停的玩家能够重新执行命令。");
}
