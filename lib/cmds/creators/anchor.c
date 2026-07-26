#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    object target;
    int arch = adminp(this_player());
    int ret, curr;

    if(!sizeof(str)) str = "me";
    if(str == "what") return "lol wat";
    if(str == "me") str = this_player()->GetKeyName();
    if(!target = present(str, environment(this_player()))){
        if(arch && (target = find_player(str))){
            write("找到用户了。");
        }
        else {
            write("他们不在这里。");
            return 1;
        }
    }
    if(living(target) && !arch && target != this_player()){
        write("你只能用这个命令固定自己。");
        return 1;
    }
    if((curr = target->GetAnchored())){
        if(target != this_player()) str = nominative(target)+"'s";
        else str = "You're ";
        if(curr < 2 && arch){
            write(capitalize(str) + " currently anchored at creator level.");
        }
        else {
            write(capitalize(str) + " already anchored.");
            return 1;
        }
    }
    ret = target->SetAnchored(1);
    if(ret == curr){
        write("什么也没发生。");
        return 1;
    }
    if(target != this_player()){ 
        tell_object(target, capitalize(this_player()->GetName())+
                " anchors you.");
    }
    else str = "yourself";
    write("你固定了"+str+"。");
    return 1;
}

string GetHelp() {
    return ("Syntax: anchor <target>\n\n"
            "Prevents the target from leaving the environment.\n"
            "See also: unanchor");
}                                                    
