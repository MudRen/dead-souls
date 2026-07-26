#include <daemons.h>
#include <lib.h>

inherit LIB_COMMAND;

int cmd(string str){
    string ret = "";

    if(!str){
        write("参见: help morse");
        return 1;
    }

    ret = morse(str);

    write("输出: "+ret);
    return 1;
}

string GetHelp() {
    return "Syntax: morse <string>\n\n"
        "Renders the provided string as morse code.\n"
        "See also: unmorse";
}
