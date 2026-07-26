#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("medtool");
    SetId( ({"tool"}) );
    SetAdjectives( ({"yautja","med","medical"}) );
    SetShort("铁血战士医疗工具");
    SetLong("这是一个手枪形状的金属装置，用于医疗紧急情况。看起来你可以尝试对自己使用它。");
    SetMass(100);
    SetDollarCost(1000);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
