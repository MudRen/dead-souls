#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them

protected void create() {
    dummy::create();
    SetKeyName("lamp");
    SetId("lamp on a post","post","lamp post","lamppost");
    SetShort("一根灯柱");
    SetLong("这是一根灯柱上的灯，夜间点亮以便镇民能看清道路。");
}
