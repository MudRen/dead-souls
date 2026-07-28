#include <lib.h>
#include "include/show.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("show");
    SetRules("OBJ LIV", "LIV OBJ", "OBJ to LIV" );
    SetErrorMessage("把什么给谁看？");
    SetHelp("Syntax: <show LIVING ITEM>\n"
            "        <show ITEM to LIVING>\n"
            "This command allows you to show something you have to "
            "someone else.\n\n"
            "See also: give, drop, get, put");
}

mixed can_show_liv_obj() {
    return can_show_obj_to_liv();
}

mixed can_show_obj_liv(mixed arg1, mixed arg2) {
    return can_show_obj_to_liv();
}

mixed can_show_obj_to_liv(mixed arg1, mixed arg2) { 
    return this_player()->CanManipulate(); }

    mixed do_show_liv_obj(object target, object what) {
        return do_show_obj_to_liv(what, target);
    }

mixed do_show_obj_liv(object what, object target) {
    return do_show_obj_to_liv(what, target);
}

mixed do_show_obj_to_liv(object what, object target) {
    this_player()->eventPrint("你把" + target->GetName() + "给" +
            what->GetShort() + "看了。");
    target->eventPrint(this_player()->GetName() + "给你看了" +
            what->GetShort() + "。");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "给" +
            target->GetName() +
            "看了" + what->GetShort() +"。",
            ({ this_player(), target }));
    what->eventShow(target);
    return 1;
}
