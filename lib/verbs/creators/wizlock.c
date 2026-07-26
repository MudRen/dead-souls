#include <lib.h>
#include <daemons.h>
#include <damage_types.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("wizlock");
    SetRules("OBJ");
    SetErrorMessage("魔法锁什么？");
    SetHelp("用法：wizlock <物品>\n\n"
            "无需钥匙即可魔法锁定一个可锁定的物品。\n"
            "另见：wizunlock");
}

mixed can_wizlock_obj(string str) {
    if(!creatorp(this_player()))
        return "此命令仅对创造者可用。";
    else return 1;
}

mixed do_wizlock_obj(object ob){
    string name;
    if(living(ob)) {
        write("你只能魔法锁定非生物物品。");
        return 1;
    }
    else name = ob->GetShort();
    if(ob->GetDoor()) ob = load_object(ob->GetDoor());
    if(!ob->GetClosed()){
        write("你无法魔法锁定它，因为它没有关闭。");
        return 1;
    }
    write("你魔法锁定了"+name+"。");
    say(this_player()->GetName()+"对"+name+"做了一个握拳的手势。",({ob}));
    ob->SetLocked(1);
    return 1;
}
