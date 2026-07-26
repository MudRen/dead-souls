#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    object thing;
    string file, content;

    if(!str){
        write("试试: help about");
        return 1;
    }

    thing = get_object(str);

    if(!thing){
        write("这里没有这样的对象。");
        return 1;
    }

    if(interactive(thing)){
        write("玩家存档文件不能使用此命令检查。");
        return 1;
    }

    file = lpc_file(base_name(thing));

    if(!file && thing->GetVirtual()){
        file = lpc_file(path_prefix(base_name(thing)));
    }

    if(file && file_exists(file)) content = read_file(file);

    if(!content){
        write("该数据目前不可用。");
        return 1;
    }

    message( "info", file + "\n", this_player() );

    return this_player()->eventPage( explode(content, "\n"), 
            MSG_SYSTEM | MSG_NOCOLOUR);
}

string GetHelp(string str) {
    return ("Syntax: about <OBJECT>\n"
            "        about here\n\n"
            "Displays the code for the object, if the file is "
            "available.\nSee also: more, find, findobj");
}
