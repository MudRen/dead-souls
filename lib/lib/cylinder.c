#include <lib.h>
#include <vendor_types.h>
inherit LIB_STORAGE;
void create(){
    ::create();
    SetKeyName("revolver cylinder");
    SetId(({"cylinder"}));
    SetShort("一个左轮手枪转轮");
    SetLong("这是容纳左轮手枪子弹的圆柱形转轮。");
    SetMass(5);
    SetValue(10);
    SetMaxCarry(10);
    SetVendorType(VT_TREASURE);
}
