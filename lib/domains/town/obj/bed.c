#include <lib.h>
#include <props.h>

inherit LIB_BED;
inherit LIB_PRESS;
inherit LIB_MANIPULATE;

int MoveBed();
int PushBed();
protected void create() {
    ::create();
    SetKeyName("king-sized bed");
    SetId( ({ "cot","bed" }) );
    SetAdjectives( ({ "large","king-sized","king-size","four-poster","four poster","big","very big"}) );
    SetShort("一张大型四柱床");
    SetLong("这是一张非常大的床，有一个大的装饰性木制床架。床上铺着柔软的天鹅绒床单。");
    SetMass(4000);
    SetMaxCarry(4000);
    SetBaseCost("silver",1500);
    SetMaxSitters(2);
    SetMaxLiers(1);
    SetPreventGet(1);
    SetManipulate( ([ "default" : (: MoveBed :) ]) );
    SetPress( ([ "default" : (: PushBed :) ]) );
}

int MoveBed(){
    send_messages("move", "$agent_name $agent_verb the bed.",
            this_player(), 0, environment(this_player()));
    environment(this_object())->OpenPassage();
    return 1;
}
int PushBed(){
    send_messages("move", "$agent_name $agent_verb the bed.",
            this_player(), 0, environment(this_player()));
    environment(this_object())->OpenPassage();
    return 1;
}
void init(){
    ::init();
}
