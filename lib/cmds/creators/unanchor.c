#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    object target;
    int arch = adminp(this_player());
    int ret, curr;

    if(!sizeof(str)) str = "me";
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
        write("你只能用这个命令解除自己的固定。");
        return 1;
    }
    if(!(curr = target->GetAnchored())){
        if(target != this_player()) str = nominative(target)+"'s";
        else str = "You're ";
        write(capitalize(str) + " already unanchored.");
        return 1;
    }
    ret = target->SetAnchored(0);
    if(ret == curr){
        write("什么也没发生。");
        return 1;
    }
    if(target != this_player()){ 
        tell_object(target, capitalize(this_player()->GetName())+
                " unanchors you.");
    }
    else str = "yourself";
    write("你解除了"+str+"的固定。");
    return 1;
}

string GetHelp() {
    return ("Syntax: unanchor <target>\n\n"
            "Removes a type of blocked movement from the target..\n"
            "See also: anchor");
}                                                    
