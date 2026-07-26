#include <lib.h>
#include <vendor_types.h>
inherit LIB_TORCH;

void create(){
    ::create();
    SetKeyName("lamp");
    SetId( ({"thing","item","thang","dingus"}) );
    SetAdjectives( ({"generic","sample","template"}) );
    SetShort("一盏高灯");
    SetLong("这是一盏嵌入地面的高灯，用来提供照明。");
    SetPreventGet("The lamp is embedded into the floor.");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetRadiantLight(25);
}

void init(){
    ::init();
    if(!GetLit() && CanBurn(this_object())){
        this_object()->eventBurn(0,0,1);
    }
}
