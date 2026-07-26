/*    /domains/Ylsrim/etc/chuch_button.c
 *    From the Dead Souls Mud Library
 *    An example dummy item that allows pressing
 *    Created by Descartes of Borg 961222
 */

#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_PRESS; // Makes the item pressable

int openDoor(object who) {
    object door = find_object("/domains/Ylsrim/etc/church_door");

    send_messages("press", "$agent_name $agent_verb了按钮。",
            who, 0, environment(who));
    if( !door->GetClosed() ) {
        return 1;
    }
    environment(who)->eventPrint("你听到门发出咔嗒声。");
    if( door->GetLocked() ) {
        door->SetLocked(0);
    }
    else {
        door->SetLocked(1);
    }
    return 1;
}

protected void create() {
    dummy::create();
    SetKeyName("button");
    SetId("button");
    SetAdjectives("big", "huge");
    SetShort("一个巨大的按钮");
    SetLong("这是一个木制按钮，你大概可以按它。");
    SetPress((: openDoor :));
}
