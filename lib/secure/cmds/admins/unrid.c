/*    /secure/cmds/admins/unrid.c
 *    created 960301 by Blitz@Dead Souls
 */

#include <lib.h>
#include <dirs.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string file;

    if(!archp(previous_object())) return 0;
    if( !sizeof(str) ) return "要恢复谁？";
    str = convert_name(str);
    file = save_file(DIR_RID + "/" + str);
    if( !file_exists(file) ) 
        return (file + ": 文件未找到，无法恢复。");
    if( rename(file, player_save_file(str)) ){
        this_player()->eventPrint("恢复失败，安全"
                "违规已记录。");
        log_file("security", "\n**** Unrid violation attempted\n"
                "Target: " + file + "\nCall Stack: " +
                sprintf("%O", previous_object(-1)));
        return 1;
    }
    this_player()->eventPrint("恢复成功。");
    PLAYERS_D->AddPlayerInfo(str);
    return 1;
}

string GetHelp(){
    return "语法: unrid <用户名>\n\n"
        "此命令恢复通过 \"rid\" 命令删除的角色。";
}

