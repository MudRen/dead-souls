#include <lib.h>

#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;


protected void create() {
    ::create();
    SetKeyName("backpack");
    SetId(({"bookbag","bag","pack"}));
    SetAdjectives(({"leather","soft","brown"}));
    SetShort("柔软的棕色皮背包");
    SetLong("这是一个中等大小的背包，由柔软的棕色皮革制成。看起来很适合忙碌的大学生用来装书。配有宽大舒适的背带，方便携带。");
    SetMass(100);
    SetDollarCost(30);
    SetCanClose(1);
    SetClosed(1);
    SetMaxCarry(500);
    SetDamagePoints(100);
    SetArmorType(A_CLOAK);
}
