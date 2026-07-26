#include <lib.h>
#include <vendor_types.h>
inherit LIB_BOOK;

void create(){
    ::create();
    SetKeyName("Log of Shame");
    SetId( ({"shamelog", "log", "book"}) );
    SetAdjectives( ({"shame"}) );
    SetShort("耻辱日志");
    SetLong("《耻辱日志》是一本包含人们应该感到羞耻的频道记录的书，奇怪的是，他们通常并不觉得。");
    SetSource("/domains/town/txt/shame");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetTitle("The Sample Book");
}

void init(){
    ::init();
}
