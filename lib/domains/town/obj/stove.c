#include <lib.h>

inherit LIB_STORAGE;


void create() {
    ::create();
    SetKeyName("stove");
    SetId(({"stove"}));
    SetAdjectives(({"large","imported","expensive"}));
    SetShort("一个大炉灶");
    SetLong("这是一个非常大的厨房炉灶，可以同时烹饪多道菜肴。");
    SetMass(5000);
    SetBaseCost("silver",1000);
    SetMaxCarry(5000);
    SetInventory(([
                "/domains/town/npc/rat" : 1
                ]));
    SetCanClose(1);
    SetClosed(1);
}

varargs mixed eventOpen(object who, string id, object tool) {
    object rat;
    mixed tmp = ::eventOpen(who, id, tool);
    if( tmp != 1 ) {
        return tmp;
    }
    rat = present("rat",this_object());
    if( rat ) {
        rat->eventMove(environment(this_object()));
        tell_room(environment(this_object()),"A mangy little rat leaps out of the stove!");
    }
    return 1;
}

void init(){
    ::init();
}
