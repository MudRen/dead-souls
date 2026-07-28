#include <lib.h>
#include <rooms.h>

mixed cmd(){
    object who = this_player();
    object env = environment(this_player());
    object room = load_object(ROOM_ARCH);
    int ret, err;

    if(env == room){
        write("你已经在那里了。");
        return 1;
    }

    if(!archp(who)){
        write("\n你真调皮，必须受到惩罚。\n");
        who->eventDestruct();
        return 1;
    }

    if(!room){
        write("管理员房间似乎出了点问题。");
        return 1;
    }

    err = catch( ret = who->eventMoveLiving(room) );

    if(err || !ret){
        write("进入管理员房间时似乎遇到了某种问题。");
    }
    return 1;
}

string GetHelp(){
    return "语法：arch\n\n"
        "传送你到管理员房间。\n参见：wiz\n";
}
