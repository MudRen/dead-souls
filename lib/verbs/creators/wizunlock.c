#include <lib.h>
#include <daemons.h>
#include <damage_types.h>
#include <modules.h>
#include ROOMS_H
#include <commands.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("wizunlock");
    SetRules("OBJ");
    SetErrorMessage("魔法解锁什么？");
    SetHelp("用法：wizunlock <物品>\n\n"
            "无需钥匙即可魔法解锁一个可锁定的物品。\n"
            "另见：wizunlock");
}

mixed can_wizunlock_obj(string str) {
    if(!creatorp(this_player()))
        return "此命令仅对创造者可用。";
    else return 1;
}

mixed do_wizunlock_obj(object ob){
    string name;

    if(living(ob)) {
        write("你只能魔法解锁非生物物品。");
        return 1;
    }
    else name = ob->GetShort();
    if(ob->GetDoor()) ob = load_object(ob->GetDoor());
    write("你魔法解锁了"+name+"。");
    say(this_player()->GetName()+"对"+name+"做了一个摊开手掌的手势。",({ob}));
    ob->SetLocked(0);
    return 1;
}
