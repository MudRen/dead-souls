//      /bin/adm/_shutdown.c
//      from the Dead Souls Mudlib
//      the shutdown command
//      created in pats by Sulam@TMI, Plura@Dead Souls, and Descartes of Borg

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;
object downer;

void ShutDown(){
    shutdown();
}

void DoSaves(){
    object *persists = objects( (: $1->GetPersistent() :) );
    foreach(object persist in persists){
        persist->eventDestruct();
    }
}

int cmd(string str) {
    downer = previous_object();
    if(downer->GetForced()){
        write("被强制尝试关闭。");
        return 1;
    }
    if(!archp(downer)) {
        write("您没有权限关闭游戏。\n");
        return 1;
    }
    if(!str) {
        write("您必须提供关闭原因作为参数。\n");
        return 1;
    }
    if(str == "cancel"){
        int cancel = EVENTS_D->eventCancelShutdown();
        if(cancel == -1){
            write("没有正在进行的关闭。");
        }
        else if(cancel > -1){
            write("关闭已取消。");
            shout("关闭已被 " + downer->GetKeyName() + " 取消。\n");
        }
        else {
            write("发生了异常情况。关闭可能无法被取消。");
        }
        return 1;
    }
    shout("Game is shut down by " + downer->GetKeyName() + ".\n");
    log_file("game_log", ctime(time())+" Game shutdown by "+
            downer->GetKeyName()+"("+str+")\n");
    foreach(object dude in users()){
        if(dude && sizeof(base_name(dude))){
            if(!archp(dude)) dude->eventForce("quit");
            else {
                downer = dude;
                unguarded( (: downer->AddCarriedMass(-99999) :) );
                unguarded( (: downer->save_player(downer->GetKeyName()) :) );
            }
        }
    }
    call_out( (: DoSaves :), 0);
    call_out( (: shutdown :), 2);
    return 1;
}

string GetHelp(){
    return ("语法：shutdown cancel\n"
            "         shutdown [原因]\n\n"
            "这将立即关闭游戏，或取消预定的关闭。请谨慎使用。\n另见：end");
}
