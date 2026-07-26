#include <lib.h>

inherit LIB_CHAIR;
inherit LIB_SWIVEL;

protected void create() {
    chair::create();
    SetKeyName("chair");
    SetId("chair");
    SetAdjectives( ({ "swivel", "small", "black" }) );
    SetShort("一把转椅");
    SetLong("这是一把小型转椅，设计雅致而低调，配有软垫座位和靠背。");
    SetMass(150);
    SetDollarCost(15);
    SetMaxSitters(1);
    SetPreventGet("The chair does not budge.");
}

void init(){
    chair::init();
}

varargs mixed eventSwivel(object who){
    if(member_array(who, GetSitters()) != -1){
        write("You swivel around in your swivel chair! Whee!");
        say(this_player()->GetName()+" swivels around in "
                +possessive(this_player())+" "+
                "swivel chair, yelling \"WHEEEE!!!\"");
        return 1;
    }
    else {
        write("You're not sitting in it!");
        return 1;
    }
}
