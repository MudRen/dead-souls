#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them

protected void create() {
    dummy::create();
    SetKeyName("wall");
    SetId(({"elevator","door","wall" }));
    SetAdjectives("call", "elevator","west");
    SetShort("一堵墙");
    SetLong("西墙上嵌入了一个看起来非常现代化的控制面板。");
    AddItem(new("/domains/town/obj/church_button"));
}
