#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_PRESS; // Makes the item pressable

int openDoor(object who) {
    object car;
    send_messages("press", "$agent_name $agent_verb the button.",
            who, 0, environment(who));
    car=load_object("/domains/town/room/elevator");
    car->SetDoor(1);
    car->CallMe(1);

}

protected void create() {
    dummy::create();
    SetKeyName("button 1");
    SetId("button","one","1");
    SetAdjectives("elevator","button","one","1");
    SetShort("一个按钮");
    SetLong("这是一个你大概可以按下的按钮。数字"1"刻在上面。");
    SetPress((: openDoor :));
}
