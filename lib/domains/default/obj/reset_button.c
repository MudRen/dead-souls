#include <lib.h>
#include ROOMS_H

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_PRESS; // Makes the item pressable

object room;

int eventResetRoom() {
    object *livings = get_livings(environment(this_object()),2);
    room = environment(this_object());
    livings->eventMove(ROOM_FURNACE);
    livings->eventDestruct();
    call_out( (: reload_room, room :), 0 );
    return 1;
}

protected void create() {
    dummy::create();
    SetKeyName("button");
    SetId(({"button","button on the wall"}));
    SetAdjectives("reset");
    SetShort("一个按钮");
    SetLong("这是一个你 probably press 的按钮。");
    SetPress((: eventResetRoom :));
}
