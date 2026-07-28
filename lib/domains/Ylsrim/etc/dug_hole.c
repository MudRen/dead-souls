/*    /domains/Ylsrim/etc/dug_hole.c
 *    From the Dead Souls Mud Library
 *    A door that is really a hole instead of a door
 *    Created by Descartes of Borg 961231
 */

#include <lib.h>

inherit LIB_DOOR;

string checkOpenDown(object who) {
    if( GetClosed() ) {
        return "你需要挖一个洞。";
    }
    else {
        return "这是沙漠沙地中的一个又深又黑的洞。";
    }
}

string checkOpenUp(object who) {
    if( GetClosed() ) {
        return "这里没有洞。";
    }
    else {
        return "它通向开阔的天空。";
    }
}

mixed CanClose() {
    return 0; // people should not be closing this manually
}

mixed CanOpen() {
    return 0; // people should not be opening this manually
}

protected void create() {
    door::create();
    SetId("down", "hole");
    SetShort("down", "沙子"); // this is what is seen when bumped into
    SetLong("down", (: checkOpenDown :));
    SetId("up", "hole");
    SetShort("up", "沙子"); // this is what is seen when bumped into
    SetLong("up", (: checkOpenUp :));
    SetClosed(1);
}
