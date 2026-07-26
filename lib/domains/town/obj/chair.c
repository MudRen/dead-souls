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
    SetPreventGet("椅子纹丝不动。");
}

void init(){
    chair::init();
}

varargs mixed eventSwivel(object who){
    if(member_array(who, GetSitters()) != -1){
        write("你在转椅上转来转去！太好玩了！");
        say(this_player()->GetName()+"在"
                +possessive(this_player())+
                "转椅上转来转去，大喊\"太好玩了！！！\"");
        return 1;
    }
    else {
        write("你没有坐在上面！");
        return 1;
    }
}
