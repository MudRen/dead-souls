#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_DONATE;

void create(){
    donate::create();
    item::create();
    SetKeyName("donation box");
    SetId( ({"box","donation box"}) );
    SetAdjectives( ({"small","wood","wooden"}) );
    SetShort("一个捐款箱");
    SetLong("这是一个小捐款箱，木制的。上面有一个投币口。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetLocalCurrency("silver");
    SetOwner("The Seventh Day Atheist Congregation");
}

string GetLong(){
    string extra = donate::GetLong();
    string base = item::GetLong();
    return base+extra;
}

void init(){
    ::init();
}

mixed CanGet(){ 
    return "这是给穷人的，你这渣滓！自己挣钱去！";
}
