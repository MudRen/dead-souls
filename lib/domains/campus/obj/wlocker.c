/*    /domains/Examples/etc/bag.c
 *    from the Dead Souls LPC Library
 *    a sample bag object
 *    created by Descartes of Borg 950529
 */

#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("locker");
    SetId(({"locker"}));
    SetAdjectives(({"metal","tall","large","weapon","weapons"}));
    SetShort("金属武器柜");
    SetLong("这是一个大型金属储物柜，设计用于存放枪支。"); 
    SetMass(3000);
    SetDollarCost(50);
    SetMaxCarry(500);
    SetInventory(([
                "/domains/campus/weap/9mil" : 5,
                //"/domains/campus/weap/m16rifle" : 5,
                //"/domains/campus/weap/50rifle" : 5,
                "/domains/campus/weap/357pistol" : 5,
                ]));
    SetCanClose(1);
    SetClosed(0);
    SetCanLock(1);
    SetLocked(0);
}
mixed CanGet(object ob) { return "The locker does not budge.";}
void init(){
    ::init();
}
