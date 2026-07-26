//	/bin/user/_save.c
//	from the Dead Souls mudlib
//	command to save the player
//	written by Descartes of Borg

#include <lib.h>

inherit LIB_DAEMON;

int cmd(){
    if(this_player()->query_disable()) {
        write("请稍等。");
        return 1;
    }
    this_player()->set_disable();
    this_player()->save_player(this_player()->GetKeyName());
    write(this_player()->GetName()+" 已保存。");
    return 1;
}

string GetHelp(){
    return ("用法: save\n\n此命令将你角色的当前状态保存到磁盘。"
            "这很重要，因为如果mud崩溃，这个文件将用于恢复你的角色。"
            "当你退出时，角色会自动保存。");
}
