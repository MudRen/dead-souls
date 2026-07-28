#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    object ob, room, where;
    string last_loc, name;
    int result;

    if( !args || args == "" ){ 
        ob = this_player();
        name = "You";
    }
    else {
        if( !(ob = find_player(convert_name(args))) && !(ob = find_living(args)) )
            return "当前不存在该生物。";
        name = "They";
    }
    if(!last_loc = ob->GetProperty("LastLocation")){
        write(name+"没有可以返回的地方。");
        return 1;
    }

    if(grepp(last_loc,"#")) where = find_object(last_loc);
    else where = load_object(last_loc);

    if(!where){
        write("该位置存在问题。");
        write(name+"留在了原地。");
        return 1;
    }

    if(environment(ob) == where){
        write(name+"已经在那里了。");
        return 1;
    }

    else result = ob->eventMoveLiving(where);

    if(ob != this_player()){
        if(result){
            message("system", "你已被 " +
                    this_player()->GetName() + " 送回上一个位置。", ob);
            message("system", "你将 " + ob->GetCapName() +
                    " 送回了其上一个位置。", this_player());
        }
        else {
            return "无法移动 " + ob->GetCapName() + "。";
        }
    }
    return 1;
}

string GetHelp() {
    return ("Syntax: return [living]\n\n"
            "Sends someone back, after a trans.\n"
            "With no arguments, sends you to your last location.\n"
            "See also: goto");
}
