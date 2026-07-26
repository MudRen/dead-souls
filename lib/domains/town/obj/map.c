#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_READ;

int ReadFunc(){
    this_player()->eventPage("/domains/town/txt/map.txt","system");
    return 1;
}

void create(){
    ::create();
    SetKeyName("town map");
    SetId(({"map","map of the town"}));
    SetAdjectives(({"small"}));
    SetShort("一张小镇地图");
    SetLong("小镇地图。尝试：read map\n");
    SetMass(1);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
    SetRead((: ReadFunc :));
}

void init(){
    ::init();
}
