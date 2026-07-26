#include <lib.h>
#include <size_types.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create() {
    ::create();
    SetKeyName("loincloth");
    SetId(({"cloth"}));
    SetAdjectives(({"loin","filthy"}));
    SetShort("一条肮脏的缠腰布");
    SetLong("这是一块非常大的布，被某个邋遢的家伙用作衣物和储物工具。");
    SetMass(100);
    SetCanClose(0);
    SetClosed(0);
    SetMaxCarry(100);
    SetArmorType(A_PANTS);
    SetSmell( ([
                "default" : "P.U.",
                ]) );
    SetMoney( ([
                "platinum" : random(5)+1,
                ]) );
    SetInventory(([
                "/domains/default/obj/vial_orange" : 1,
                "/domains/town/obj/cavetroll_key" : 1,
                ]));
    SetSize(S_LARGE);
}

void init(){
    ::init();
}
