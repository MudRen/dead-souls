#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_WEAR; // Makes the item pressable

varargs mixed eventWear(object who) {
    return 1;
}

protected void create() {
    dummy::create();
    SetKeyName("hood");
    SetId("cloak hood","cloak's hood");
    SetShort("一个兜帽");
    SetLong("斗篷上的兜帽。");
    SetInvis(0);
    //SetWear((: eventWear :));
}
