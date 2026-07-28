#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("disarm");
    SetRules("OBJ");
    SetErrorMessage("解除什么武装？");
    SetHelp("Syntax: <disarm OBJ with OBJ>\n\n"
            "Use this command to try to disarm a boobytrapped object, like "
            "a door or a chest.\n\n"
            "See also: close, open, pick, disarm");
}

varargs mixed can_disarm_obj(mixed args...) {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

varargs mixed do_disarm_obj(object target) {
    return target->eventDisarm(this_player());
}
