#include <lib.h>

inherit LIB_DAEMON;

varargs int cmd(string args){
    int status = this_player()->GetProperty("noclip");
    string sstatus = "正";
#if !(GRID)
    write("此功能已禁用。");
    return 1;
#endif
    if(!status) sstatus = "没有";
    if(!args){
        write("你"+sstatus+"在使用穿墙模式。");
        return 1;
    }
    if(args == "on"){
        if(status) write("你已经在穿墙模式中了。");
        else write("你启用了穿墙模式。");
        this_player()->SetProperty("noclip", 1);
        return 1;
    }

    if(args == "off"){
        if(!status) write("你已经不在穿墙模式中了。");
        else write("你禁用了穿墙模式。");
        this_player()->SetProperty("noclip", 0);
        return 1;
    }

    write("试试: help noclip");
    return 1;
}

string GetHelp(){
    return ("Syntax: noclip [ on | off ]\n\n"+
            "Allows you to travel to adjacent rooms known to the "+
            "mud, even if a door is in the way or there is no "+
            "explicit exit in that direction.\nSee also: "+
            "showgrid, wizmap, minimap, prox");
}
