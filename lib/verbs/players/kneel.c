#include <lib.h>
#include <position.h>
#include <rounds.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("kneel");
    SetRules("down","");
    SetErrorMessage("跪下？");
    SetSynonyms("genuflect");
    SetHelp("Syntax: kneel <down>\n\n"
            "Allows you to kneel.\n"
            "See also: sit, stand, lie");
}

mixed can_kneel_down() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }

    if( this_player()->GetPosition() == POSITION_KNEELING ) {
        return "你已经跪着了！";
    }

    if(!environment(this_player())->CanKneel(this_player())){
        return "你不能在这里跪下。";
    }

    return 1;
}

mixed can_kneel(){
    return can_kneel_down();
}

mixed can_kneel_word_obj() {
    return can_kneel_down();
}

mixed can_kneel_down_word_obj() {
    return can_kneel_down();
}

mixed do_kneel_down() {
    return this_player()->eventKneel();
}

mixed do_kneel(){
    return do_kneel_down();
}

mixed do_kneel_word_obj(string word, object target) {
    return this_player()->eventKneel(target);
}

mixed do_kneel_down_word_obj(string word, object target) {
    return this_player()->eventKneel(target);
}
