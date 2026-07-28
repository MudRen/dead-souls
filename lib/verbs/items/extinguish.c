#include <lib.h>
#include "include/extinguish.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("extinguish");
    SetSynonyms("douse");
    SetRules("OBS");
    SetErrorMessage("熄灭什么？");
    SetHelp("Syntax: <extinguish OBJECT>\n\n"
            "Extinguish a burning thing like a torch or a lamp.\n\n"
            "See also: light");
}

mixed can_extinguish_obj() {
    return this_player()->CanManipulate();
}

mixed do_extinguish_obj(object target) {
    return do_extinguish_obs(({ target }));
}

mixed do_extinguish_obs(mixed *targs) {
    object *obs;
    string tmp;

    if( !sizeof(targs) ) {
        this_player()->eventPrint("没有这样的东西可以熄灭。");
        return 1;
    }
    obs = filter(targs, (: objectp :));
    if( !sizeof(obs) ) {
        mixed *ua;

        ua = unique_array(targs, (: $1 :));
        foreach(string *list in ua) this_player()->eventPrint(list[0]);
        return 1;
    }
    obs = filter(obs, (: $1->eventExtinguish(this_player()) :));
    if( !sizeof(obs) ) return 1;
    tmp = item_list(obs);
    this_player()->eventPrint("你熄灭了" + tmp + "。");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "熄灭了" + tmp + "。",
            this_player());
    return 1;
}

