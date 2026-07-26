#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create(){
    ::create();
    SetKeyName("necklace");
    SetId(({"necklace","chain" "locket"}));
    SetAdjectives(({"silver","braided","finest"}));
    SetShort("一条银项链");
    SetLong("一条编织链，由最优质的银制成。上面有一个挂坠。");  
    SetMass(50);
    SetMaxCarry(300);
    SetBaseCost("silver",1);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_COLLAR);
    SetItems(([
                ({"locket"}) : "It bears the name of the man that Brandy loved.",
                ])); 
}

void init(){
    ::init();
}
