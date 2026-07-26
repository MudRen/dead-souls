#include <lib.h>
#include <vendor_types.h>
inherit LIB_BOOK;

void create(){
    ::create();
    SetKeyName("administrator's guidebook");
    SetId( ({"guidebook", "book", "guide", "administrators guide", "administrators guidebook"}) );
    SetAdjectives( ({"admin's", "admin", "admins", "administrator", "administrators", "reference"}) );
    SetShort("管理员指南");
    SetLong("这是Dead Souls管理员的参考文本。");
    SetNoCondition(1);
    SetSource("/doc/guide");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetTitle("Administrator's Guidebook");
}
void init(){
    ::init();
}
