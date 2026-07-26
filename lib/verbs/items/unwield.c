/*    /verbs/items/unwield.c
 *    From the Dead Souls Mud Library
 *    Allows players to stop wielding a weapon
 *    Created by Descartes of Borg 960207
 *    Version: @(#) unwield.c 1.2@(#)
 *    Last modified: 97/01/01
 */

#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("unwield");
    SetRules("OBS");
    SetErrorMessage("卸下什么武器？");
    SetHelp("用法：unwield <武器>\n"
            "      unwield all [of <武器>]\n\n"
            "此动词允许你卸下你当前装备的武器。\n\n"
            "另见：get, remove, wear, wield");
}

mixed can_unwield_obj(string verb) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return 1;
}

mixed do_unwield_obj(object ob) {
    return ob->eventUnequip(this_player());
}

mixed do_unwield_obs(mixed* targs) {
    object* obs;

    if( !sizeof(targs) ) {
        this_player()->eventPrint("没有这样的东西可以卸下。");
        return 1;
    }
    obs = filter(targs, (: objectp :));
    if( !sizeof(obs) ) {
        mapping messages = unique_mapping(targs, (: $1 :));

        foreach(string msg in keys(messages)) {
            this_player()->eventPrint(msg);
        }
        return 1;
    }
    foreach(object item in obs) {
        do_unwield_obj(item);
    }
    return 1;
}
