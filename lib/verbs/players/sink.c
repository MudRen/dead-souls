#include <lib.h>
#include <position.h>
#include <rounds.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("sink");
    SetRules("", "down");
    SetErrorMessage("下沉？");
    SetHelp("Syntax: sink [down]\n"
            "Allows you to stop swimming, or otherwise attempt to "
            "sink in your current medium.\n"
            "See also: sit, lie, stand, swim, fly");
}

mixed can_sink_down() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了！";
    }
    if(this_player()->CanSink()){
        return "你不能在这里下沉。";
    }
    if( this_player()->GetPosition() == POSITION_FLOATING ) {
        return "你已经在漂浮了！";
    }
    return 1;
}

mixed can_sink(){
    return can_sink_down();
}

mixed do_sink_down(){
    this_player()->SetPosition(POSITION_FLOATING);
    return this_player()->eventSink();
}

mixed do_sink() {
    return do_sink_down();
}
