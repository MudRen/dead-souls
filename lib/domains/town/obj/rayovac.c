#include <lib.h>
#include <vendor_types.h>
inherit "/lib/flashlight";

void create(){
    ::create();
    SetKeyName("flashlight");
    SetId( ({"fl","flashlight","light","torch","flashlite", "rayovac"}) );
    SetAdjectives( ({"plastic","small","cheap","rayovac","Rayovac"}) );
    SetShort("一个小塑料手电筒");
    SetLong("这是一个廉价的Rayovac品牌手电筒。");
    SetMass(10);
    SetBaseCost("silver",10);
    SetLightLevel(16);
    SetMinCells(2);
    SetMaxCells(2);
    SetCellType("D");
    Lit=0;
    SetVendorType(VT_TREASURE);
    SetInventory(([
                "/domains/town/obj/dcell_crappy":2
                ]));

}
void init(){
    ::init();
}
