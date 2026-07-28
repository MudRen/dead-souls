#include <lib.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("apply");
    SetRules("OBJ WRD OBJ", "OBJ OBJ");
    SetErrorMessage("把什么用在什么上？");
    SetHelp("Syntax: apply ITEM to OBJECT\n\n"
            "Allows you to put one thing up against another.\n\n"
            "See also: turn, activate, install");
}

mixed can_apply_obj_word_obj() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    return this_player()->CanManipulate();
}

mixed can_apply_obj_obj() {
    return can_apply_obj_word_obj();
}

mixed do_apply_obj_word_obj(object appliance, object target) {
    return appliance->eventApply(this_player(), target );
}

mixed do_apply_obj_obj(object appliance, object target) {
    return do_apply_obj_word_obj(appliance, target);
}
