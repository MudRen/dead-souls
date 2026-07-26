#include <lib.h>
#include <rooms.h>

mixed cmd(){
    object who = this_player();
    object env = environment(this_player());
    object room = load_object(ROOM_WIZ);
    int ret, err;

    if(!room){
        write("巫师房间似乎存在问题。");
        return 1;
    }

    if(env && env == room){
        write("你已经在巫师房间了！");
        return 1;
    }

    err = catch( ret = who->eventMoveLiving(room) );

    if(err || !ret){
        write("进入巫师房间时似乎出现了问题。");
    }

    return 1;
}

string GetHelp(){
    return ("Syntax: wiz\n\n"
            "Transports you to the wiz room.");
}
