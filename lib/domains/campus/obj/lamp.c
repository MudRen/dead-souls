#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them

protected void create() {
    dummy::create();
    SetKeyName("lamp");
    SetId("lamp on a post","post","lamp post","lamppost");
    SetShort("路灯");
    SetLong("这是一盏柱子上的灯，夜间点亮以便镇民找到路。");
}
