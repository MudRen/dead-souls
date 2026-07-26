#include <lib.h>
#include ROOMS_H
#include <daemons.h>
#include <function.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("dismount");
    SetRules("","LIV", "from LIV");
    SetErrorMessage("下什么？");
    SetHelp("语法：dismount <生物>\n\n"
            "此命令允许你从骑乘的"
            "生物身上下来。\n"
            "参见：mount, befriend, abandon");
}

mixed can_dismount_liv() {
    if(this_player()->CanManipulate()) 
        return bool_reverse(this_player()->GetParalyzed());
}

mixed can_dismount_from_liv() {
    return can_dismount_liv();
}

mixed can_dismount() {
    return can_dismount_liv();
}

mixed do_dismount_liv(object ob) {
    return ob->eventDismount(this_player());
}

mixed do_dismount_from_liv(object ob) {
    return do_dismount_liv(ob);
}

mixed do_dismount() {
    object mount = this_player()->GetProperty("mount");
    if(mount) return do_dismount_liv(mount);
    if(base_name(environment(this_player())) == LIB_CORPSE){
        object new_env = environment(environment(this_player()));
        if(!new_env) new_env = find_object(ROOM_START);
        else {
            write("你从死去的坐骑上下来了。");
            say(this_player()->GetName()+"从"+possessive(this_player())+
                    "死去的坐骑上下来了。");
        }
        this_player()->eventMoveLiving(new_env);
    }
    else return write("你似乎没有坐骑。");

}
