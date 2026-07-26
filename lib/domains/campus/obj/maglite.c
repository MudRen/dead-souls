#include <lib.h>
#include <vendor_types.h>
inherit "/lib/flashlight";


void create(){
    ::create();
    SetKeyName("maglite");
    SetId( ({"fl","flashlight","light","flashlite","Maglite"}) );
    SetAdjectives( ({"powerful","heavy","large","Maglite"}) );
    SetShort( "大手电筒" );
    SetLong("这是一个强大、沉重的Maglite品牌手电筒。");
    SetMass(20);
    SetDollarCost(40);
    SetLightLevel(20);
    SetMinCells(4);
    SetMaxCells(4);
    SetCellType("D");
    Lit=0;
    SetVendorType(VT_TREASURE);

    SetInventory(([
                "/domains/campus/obj/dcell_good":4
                ]));

}
void init(){
    ::init();
}
