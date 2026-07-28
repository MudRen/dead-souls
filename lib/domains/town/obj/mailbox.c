#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("mailbox");
    SetId( ({"mailbox", "box"}) );
    SetAdjectives( ({ "generic","nondescript" }) );
    SetShort("一个小邮箱");
    SetLong("这是一个立在白色房子前面的小邮箱。");
    SetCanClose(1);
    SetMass(274);
    SetBaseCost("silver",1);
    SetMaxCarry(100);
    SetPreventGet("你拿不了那个！");
}

void init(){
    ::init();
}
