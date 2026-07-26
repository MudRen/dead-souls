#include <lib.h>
#include <vendor_types.h>
inherit LIB_BOOK;

void create(){
    ::create();
    SetKeyName("generic book");
    SetId( ({"book"}) );
    SetAdjectives( ({"generic","sample","template"}) );
    SetShort("普通书籍");
    SetLong("这是一本大部分空白的书。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetTitle("示例之书");
}
void init(){
    ::init();
}
