#include <lib.h>
#include <vendor_types.h>
inherit LIB_DIE;


void create(){
    ::create();
    SetKeyName("die");
    SetId( ({ "implement"}) );
    SetAdjectives( ({"6","six","sided","six-sided","6-sided"}) );
    SetShort("一个六面骰子");
    SetLong("一个典型的博彩用具。橙色，上面有六个面，分别刻着数字1到6。");
    SetMass(2);
    SetBaseCost("silver",1);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
