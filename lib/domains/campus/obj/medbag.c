/*    /domains/Examples/etc/bag.c
 *    from the Dead Souls LPC Library
 *    a sample bag object
 *    created by Descartes of Borg 950529
 */

#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bag");
    SetId( ({ "medical bag" }) );
    SetAdjectives( ({ "small", "cloth", "a" }) );
    SetShort("小布袋");
    SetLong("这是一个简单的布袋，用来装东西。上面印着：\"A.S. Clepius的财产\"");
    SetMass(274);
    SetDollarCost(1);
    SetMaxCarry(100);
}
void init(){
    ::init();
}
