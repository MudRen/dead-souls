#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str){ 
    mapping stargates;
    string *gates;
    string gatename;
    int err;
    object sgd;

    err = catch( sgd = load_object(STARGATE_D) );

    if(!sgd || err){
        write("星门守护进程似乎存在问题。");
        return 1;
    }

    stargates = STARGATE_D->GetStargates();

    if(sizeof(stargates)) gates = keys(stargates);

    if(!gates){
        write("没有已知的星门。");
        return 1;
    }

    if(!str){
        write("已知的星门:");
        write(implode(gates, ", "));
        return 1;
    }

    gatename = lower_case(str);

    if(member_array(gatename, gates) == -1){
        write("未知的星门: \""+str+"\"");
        return 1;
    }

    write(str);
    foreach(mixed key, mixed val in stargates[gatename]){
        write(key + ": " + val);
    }

    return 1;
}

string GetHelp() {
    return ("Syntax: stargate [name]\n\n"
            "Without an argument, lists known stargates. If the name "
            "of a stargate is specified, information on it is listed.");
}                                                    
