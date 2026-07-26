#include <lib.h>
#include <vendor_types.h>
inherit LIB_BOOK;

void create(){
    ::create();
    SetKeyName("builder's guidebook");
    SetId( ({"text","guidebook", "book", "guide", "builders guide", "builders guidebook"}) );
    SetAdjectives( ({"builder's", "builder", "builders", "reference"}) );
    SetShort("一本建造者指南");
    SetLong("这是Dead Souls建造者的参考文本。");
    SetNoCondition(1);
    SetSource("/doc/bguide");
    SetMass(20);
    SetVendorType(VT_TREASURE);
    SetTitle("Builder's Guidebook");
}
void init(){
    ::init();
}
