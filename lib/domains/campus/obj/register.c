#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("register");
    SetId(({"register","machine"}));
    SetAdjectives(({"cash","metal"}));
    SetShort("收银机");
    SetLong("这是一台用于现金交易的金属机器。");
    SetMass(200);
    SetBaseCost("silver",50);
    SetMaxCarry(10);
    SetPreventPut("You cannot put this in there!");
    SetMoney( ([
                "dollars" : random(200),
                ]) );
    SetCanClose(1);
    SetClosed(1);
}

void init(){
    ::init();
}
