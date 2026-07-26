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
    SetLong("这是一个大型结实的背包，由某种坚固的帆布状材料制成。看起来适合你可能遇到的任何冒险。");
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
