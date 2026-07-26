#include <lib.h>
#include <daemons.h>
#include <damage_types.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("zap");
    SetRules("LVS");
    SetErrorMessage("电击什么？");
    SetHelp("用法：zap <生物>\n\n"
            "对一个生物造成巨大伤害。\n"
            "另见：dest, resurrect");
}

mixed can_zap_liv(string str) {
    if(!creatorp(this_player()))
        return "此命令仅对创造者可用。";
    else return 1;
}

mixed do_zap_liv(object ob){
    string name;
    int mhp;

    if(!living(ob)) {
        write("你只能电击活物。");
        return 1;

    }
    else name = ob->GetName();
    mhp = ob->GetMaxHealthPoints();
    if(!mhp) mhp = 99999;
    mhp *= 5;
    write("你电击了"+name+"。");
    say(this_player()->GetName()+"举起手，%^RED%^电击%^RESET%^了"+
            name+"！",({ob}));
    tell_object(ob,this_player()->GetName()+"举起手，"+
            "%^RED%^电击%^RESET%^了你！");
    ob->eventReceiveDamage(this_player(),DEATHRAY,mhp,0,({ob->GetTorso()}));
    return 1;
}

mixed do_zap_lvs(object *obs) {
    foreach(object ob in obs){
        if(!(ob == this_player())) do_zap_liv(ob);
    }
    return 1;
}
