/*    /cmds/creator/which.c
 *    From the Dead Souls Mud Library
 *    gives you a list of directories in which a command may be found
 *    created by Descartes of Borg 950913
 *    Version: @(#) which.c 1.2@(#)
 *    Last modified: 96/10/08
 */

#include <lib.h>
#include <daemons.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string* dirs;
    mixed *aa;
    string dir, msg = "", ret;
    int isverb;
    dirs = ({});

    isverb = 0;

    if( !args ) {
        return "你想查询哪个命令的信息？";
    }
    if(member_array(args,keys(VERBS_D->GetVerbs())) != -1){
        dirs += ({ (VERBS_D->GetVerbs())[args] });
        isverb = 1;
    }
    else dirs = CMD_D->GetPaths(args);
    if(sizeof(dirs)){
        msg += args + ":";
        foreach(dir in dirs) {
            if(isverb) msg += "\n\t" + dir;
            else msg += "\n\t" + dir + "/" + args + ".c";
        }
    }
    aa = filter(this_player()->GetCommands(), (: $1[0] == $(args) :) );
    if(sizeof(aa)){
        msg += "\n";
        msg += args + " 是一个 add_action()，定义于 "+identify(aa[0][2]);
    }
    ret = this_player()->GetAlias(args);
    if(ret){
        msg += "\n"+ args + " 是一个别名，展开为: "+ret;
    }
    if( (ret = this_player()->GetXverb(args)) ){
        msg += "\n"+ args + " 是一个 xverb，展开为: "+ret;
    }
    if(member_array(args, SOUL_D->GetEmotes()) != -1){
        msg += "\n"+ args + " 是一个表情(emote)。";
    }
    if(!sizeof(msg)) msg = args +": 未找到。";
    previous_object()->eventPrint(msg, MSG_SYSTEM);
    return 1;
}

string GetHelp() {
    return ("语法: which [命令]\n\n"
            "列出可以找到指定命令对象的所有位置。\n"
            "另见: help, man");
}
