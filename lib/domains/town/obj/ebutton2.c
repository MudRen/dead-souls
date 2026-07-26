#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_PRESS; // Makes the item pressable

int openDoor(object who) {
    object car;
    send_messages("press", "$agent_name $agent_verb the button.",
            who, 0, environment(who));
    car=load_object("/domains/town/room/elevator");
    car->SetDoor(1);
    car->CallMe(2);

}

protected void create() {
    dummy::create();
    SetKeyName("button b");
    SetId("b","button","two","B", "button B");
    SetAdjectives("b", "elevator","button","basement","B");
    SetShort("一个按钮");
    SetLong("这是一个你大概可以按下的按钮。字母"B"刻在上面。");
    SetPress((: openDoor :));
}
