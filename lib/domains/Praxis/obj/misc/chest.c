/*    /d/Praxis/obj/misc/chest.c
 *    from Nightmare IV
 *    a lockable treasure chest
 *    created by Descartes of Borg 940212
 */

#include <lib.h>
#include <objects.h>

inherit LIB_STORAGE;

void create() {
    object money;

    ::create();
    SetKeyName("chest");
    SetId( ({ "chest" }) );
    SetAdjectives( ({ "orc", "treasure" }) );
    SetShort("一个兽人宝箱");
    SetLong("一个巨大的宝箱，上面有一把大锁。");
    SetMass(2000);
    SetValue(100);
    SetMaxCarry(2000);
    SetCanClose(1);
    SetCanLock(1);
    SetPreventPut("宝箱？想得美！");
    SetProperty("magic hold", 10);
    SetKey("orc_treasure");
    money = new(LIB_PILE);
    money->SetCurrency("platinum", random(5));
    money->SetCurrency("gold", random(100));
    money->SetCurrency("copper", random(10000));
    money->move(this_object());
    SetClosed(1);
    SetLocked(1);
}
