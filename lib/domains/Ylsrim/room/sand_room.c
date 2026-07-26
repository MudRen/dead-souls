/*    /domains/Ylsrim/room/sand_room.c
 *    From the Dead Souls Mud Library
 *    An example of a room in which you can dig
 *    Created by Descartes of Borg 961231
 */

#include <lib.h>

inherit LIB_ROOM;
inherit LIB_DIG;  // inherit this to add dig functionality
inherit LIB_BURY;  // inherit this to add bury functionality

int eventEnterDesert(){
    this_player()->eventMoveLiving(load_object("/domains/Ylsrim/virtual/server")->compile_object("/domains/Ylsrim/virtual/desert/7,7"));
    return 1;
}

// This function gets called when someone tries to bury the hole
mixed buryHole(object who, object shovel) {
    int closed;
    closed = "/domains/Ylsrim/etc/dug_hole"->GetClosed();

    if( closed ) {
        who->eventPrint("也许你想挖洞？");
        return 1;
    }
    send_messages("bury", "$agent_name $agent_verb了沙中一个深深的洞。", who, 0, environment(who));
    "/domains/Ylsrim/etc/dug_hole"->SetClosed(1);
    return 1;
}

// This function gets called when someone tries to dig
mixed digHole(object who, object shovel) {
    int closed;
    closed = "/domains/Ylsrim/etc/dug_hole"->GetClosed();

    if( !closed ) {
        who->eventPrint("也许你想填埋这个洞？");
        return 1;
    }
    send_messages("dig", "$agent_name $agent_verb了沙中一个深深的洞。", who, 0, environment(who));
    "/domains/Ylsrim/etc/dug_hole"->SetClosed(0);
    return 1;
}

// This function is set in SetLong() to describe the room differently
// when the hole is open.
string describeRoom() {
    string str = "你就在伊尔斯利姆西边边缘的外面。"
        "你现在站在开阔的沙漠中，干燥的风耗尽了你所有的力气。"
        "除了无尽的沙子，这里什么都没有。"
        "你大概只能坐下来挖沙子了。";
    SetExits( ([ 
                "east" : "/domains/Ylsrim/room/kaliid7",
                "down" : "/domains/Ylsrim/room/sand_hole",
                ]) );

    if( "/domains/Ylsrim/etc/dug_hole"->GetClosed() ) {
        return str;  // no hole to see
    }
    else {
        return str + "  沙地中央出现了一个洞。";
    }
}

protected void create() {
    room::create();
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("伊尔斯利姆外的沙漠");
    SetLong((: describeRoom :));
    AddItem("sand", "单调的沙地一直延伸到地平线。");
    AddItem("ylsrim", "它在这里的东边。");
    SetInventory( ([ "/domains/Ylsrim/etc/shovel" : 1 ]) );
    // use a door to act as a hole, as that is what the hole really is
    SetDoor("down", "/domains/Ylsrim/etc/dug_hole");
    // this tells the room to call this function when a player digs
    SetDig((: digHole :));
    // this tells the room what to call when a player buries the hole
    SetBury((: buryHole :));
}
void init(){
    ::init();
}
