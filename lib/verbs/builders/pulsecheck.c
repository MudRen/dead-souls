#include <lib.h>
#include <daemons.h>
#include <damage_types.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("pulsecheck");
    SetRules("LVS");
    SetErrorMessage("pulsecheck what?");
    SetHelp("语法: pulsecheck <CREATURE>\n\n"
            "检查一个生物的心跳。\n"
            "另见: zap");
}

mixed can_pulsecheck_liv(string str) {
    if(!creatorp(this_player())) return "此命令仅适用于建造者和创造者。";
    else return 1;
}

mixed do_pulsecheck_liv(object ob){
    string name;
    int mhp;

    if(!living(ob)) {
        write("你只能检查活着的生物。");
        return 1;

    }
    write(ob->GetName()+"的心跳是"+query_heart_beat(ob)+"。");
    write(ob->GetName()+"的心率是"+ob->GetHeartRate()+"。\n");
    return 1;
}

mixed do_pulsecheck_lvs(object *obs) {
    foreach(object ob in obs){
        if(!(ob == this_player())) do_pulsecheck_liv(ob);
    }
    return 1;
}
