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
        write("\nYou are naughty, and must be punished.\n");
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
    return "Syntax: arch\n\n"
        "Transports you to the arch room. \nSee also: wiz\n";
}
