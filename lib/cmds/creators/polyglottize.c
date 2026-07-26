#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    object target;

    if(!str || str == "") str = "me";

    if(str == "me") str = this_player()->GetKeyName();
    if(!target = present(str, environment(this_player()))){
        write("他们不在这里。");
        return 1;
    }
    if(!living(target)) {
        write("那不是活物。");
        return 1;
    }
    if(creatorp(target) && !archp(this_player()) &&
            target != this_player()){
        write("这不太礼貌。");
        tell_player(target,capitalize(this_player()->GetKeyName())+
                " just tried to polyglottize you.");
        return 1;
    }

    target->SetPolyglot(1);
    if(target == this_player()) str = "yourself";
    else str = capitalize(str);
    write("你使"+str+"获得了通晓语言的能力。");
    if(target != this_player()) 
        tell_object(target, capitalize(this_player()->GetKeyName())+" polyglottizes you.");
    return 1;
}

string GetHelp() {
    return ("Syntax: polyglottize <target>\n\n"
            "Make the target able to understand all languages.");
}                                                    
