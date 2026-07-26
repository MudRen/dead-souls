#include <lib.h>

inherit LIB_CHAIR;
inherit LIB_ROCK;

protected void create() {
    chair::create();
    SetKeyName("chair");
    SetAdjectives( ({"simple", "wood", "wooden", "rocking", "classic"}) );
    SetId("chair");
    SetShort("一把木摇椅");
    SetLong("一把简单的木摇椅，采用小镇乡村地区常见的经典实用风格。");
    SetMass(100);
    SetDollarCost(15);
    SetMaxSitters(1);
    SetPreventGet("The chair does not budge.");
}

void init(){
    ::init();
}

varargs mixed eventRock(object who){
    if(member_array(who, GetSitters()) != -1){
        write("You rock back and forth in your chair.");
        say(this_player()->GetCapName()+" rocks back and forth "+
                "on "+possessive(who)+" rocking chair.");
        return 1;
    }
    else {
        write("You're not sitting in it!");
        return 1;
    }
}
