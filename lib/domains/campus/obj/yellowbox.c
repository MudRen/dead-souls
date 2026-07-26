/*    /domains/Examples/etc/bag.c
 *    from the Dead Souls LPC Library
 *    a sample bag object
 *    created by Descartes of Borg 950529
 */

#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("yellowbox");
    SetId( ({ "box","yellowbox","ybox" }) );
    SetAdjectives( ({ "small", "plastic","yellow", "a" }) );
    SetShort("小%^YELLOW%^黄色%^RESET%^塑料盒");
    SetLong("这是一个简单的塑料盒，用来装东西。它是%^YELLOW%^黄色%^RESET%^的，上面印有可爱的虚拟校区标志。");
    SetMass(274);
    SetDollarCost(1);
    SetMaxCarry(100);
    SetCanClose(1);
    SetClosed(0);
    //    SetPreventPut("You cannot put this in there!");
}
void init(){
    ::init();
}
