#include <lib.h>
#include <vendor_types.h>
inherit LIB_DIE;


void create(){
    ::create();
    SetKeyName("die");
    SetId( ({ "implement"}) );
    SetAdjectives( ({"20","twenty","sided","twenty-sided","20-sided"}) );
    SetShort("一个二十面骰子");
    SetLong("一个典型的博彩用具。橙色，上面有二十个面，分别刻着数字1到20。");
    SetDenominator(20);
    SetMass(4);
    SetBaseCost("silver",5);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
