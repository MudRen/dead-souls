/*    /domains/Examples/etc/bag.c
 *    from the Dead Souls LPC Library
 *    a sample bag object
 *    created by Descartes of Borg 950529
 */

#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("box");
    SetId( ({ "box" }) );
    SetAdjectives( ({ "small", "plastic","green", "a" }) );
    SetShort("小塑料盒");
    SetLong("这是一个简单的塑料盒子，用来装东西。它是绿色的，上面有一个可爱的虚拟校园标志。");
    SetMass(274);
    SetDollarCost(1);
    SetMaxCarry(10);
    //    SetPreventPut("You cannot put this in there!");
}
void init(){
    ::init();
}
