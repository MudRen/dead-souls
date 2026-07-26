/*    /d/Praxis/obj/misc/bag.c
 *    from Nightmare IV
 *    a simple bag
 *    created by Descartes of Borg 940212
 */

#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bag");
    SetId( ({ "bag" }) );
    SetAdjectives( ({ "small", "cloth", "a" }) );
    SetShort("一个小布袋");
    SetLong("这是一个用来装东西的简单布袋。");
    SetMass(274);
    SetValue(50);
    SetMaxCarry(500);
    SetPreventPut("你不能把那个放进去！");
}
