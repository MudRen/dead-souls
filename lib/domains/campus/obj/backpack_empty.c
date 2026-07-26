#include <lib.h>

#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create() {
    ::create();
    SetKeyName("backpack");
    SetId(({"bag","pack"}));
    SetAdjectives(({"sturdy","green","olive","olive-green","od green","od-green"}));
    SetShort("结实的橄榄绿背包");
    SetLong("This is a large, sturdy backpack made of some sort of "
            "strong, canvas-like material. It appears suitable "+
            "for just about any adventure you'd find yourself in.");
    SetMass(100);
    SetBaseCost("silver", 40);
    SetCanClose(1);
    SetClosed(0);
    SetMaxCarry(500);
    SetDamagePoints(100);
    SetArmorType(A_VEST);

}
void init(){
    ::init();
}
