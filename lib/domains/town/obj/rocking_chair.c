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
    SetPreventGet("椅子纹丝不动。");
}

void init(){
    ::init();
}

varargs mixed eventRock(object who){
    if(member_array(who, GetSitters()) != -1){
        write("你在椅子上前后摇晃。");
        say(this_player()->GetCapName()+"在"
                +possessive(who)+"摇椅上前后摇晃。");
        return 1;
    }
    else {
        write("你没有坐在上面！");
        return 1;
    }
}
