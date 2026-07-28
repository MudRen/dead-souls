/*    /secure/cmds/admins/unlink.c
 *    from the Dead Souls Mud Library
 *    unlink PLAYER
 *    created by Descartes of Borg 951216
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string primary, secondary;
    mixed tmp;

    if( !archp(previous_object()) ) return 0;
    if( !args || args == "" ) return "要解除谁的关联？";
    if( sscanf(args, "%s from %s", secondary, primary) != 2 )
        return "要解除谁的关联？";
    tmp = CHARACTER_D->eventUnlink(primary, secondary);
    if( !tmp ) return "解除关联失败。";
    else if( tmp == 1 ){
        this_player(1)->eventPrint("已解除关联。");
        return 1;
    }
    else return tmp;
}

string GetHelp(){
    return ("语法: unlink <角色名> from <主角色>\n\n"
            "解除指定角色与其主要角色的关联。如果要解除关联的玩家"
            "本身是主角色且有超过两个关联角色，第一个关联角色"
            "将成为主角色。否则整个关联将被移除。");
}
