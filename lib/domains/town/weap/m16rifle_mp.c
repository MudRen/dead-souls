#include <lib.h>
#include <vendor_types.h>
#include <damage_types.h>
inherit LIB_FIREARM;

void CheckMP();

void create(){
    ::create();
    SetKeyName("rifle");
    SetId(({"rifle","m16","M-16","weapon"}));
    SetAdjectives(({"m-16","M-16","m16","M16","assault","colt"}));
    SetShort("一把M-16突击步枪");
    SetLong("这把流线型黑色武器一直是军队的主力武器。它发射5.56毫米子弹，精度很高。");
    SetCaliber(223);
    SetFirearmType("auto");
    SetFirearmName("rifle");
    SetAmmoType("nato");
    SetMass(60);
    SetDollarCost(1000);
    SetHands(2);
    SetClass(20);
    SetWeaponType("blunt");
    SetDamageType(BLUNT);
    SetVendorType(VT_WEAPON);
}

void init() {
    ::init();
    CheckMP();
}

int AddClip(){
    object env = environment();
    object clip = present("clip",this_object());
    if(!clip && env && !(clip = present("clip",env))){
        clip = new("/domains/town/obj/223clip");
    }
    if(clip) clip->eventMove(this_object());
    return 1;
}

void CheckMP(){
    if(base_name(environment(this_object())) == "/domains/town/npc/mp"){
        AddClip();
        SetLoaded(1);
        SetAmmo(30);
        SetMag(1);
    }
}

