#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_READ;


int TestFunc(){
    this_player()->eventPage("/domains/campus/txt/map.txt","system");
    return 1;
}
void create(){
    ::create();
    SetKeyName("building map");
    SetId(({"map","map of the administrative building","small map of the administrative building"}));
    SetAdjectives(({"small"}));
    SetShort("行政楼小地图");
    SetLong("行政楼的地图。试试：read map \n");
    SetMass(0);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
    SetRead((: TestFunc :));
}
void init(){
    ::init();
}
