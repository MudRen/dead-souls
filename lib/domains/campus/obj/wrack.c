/*    /domains/Examples/etc/bag.c
 *    from the Dead Souls LPC Library
 *    a sample bag object
 *    created by Descartes of Borg 950529
 */

#include <lib.h>

inherit LIB_STORAGE;


void create() {
    ::create();
    SetKeyName("rack");
    SetId(({"wrack"}));
    SetAdjectives(({"wooden","large","weapon","weapons"}));
    SetShort("木质武器架");
    SetLong("这是一个大型木质架子，设计用于存放常规或近战武器。它嵌入墙壁中。");
    SetMass(3000);
    SetDollarCost(500);
    SetMaxCarry(5000);
    SetInventory(([
                "/domains/campus/weap/dagger" : 5,
                "/domains/campus/weap/sword" : 5,
                "/domains/campus/weap/sharpsword" : 5,
                "/domains/campus/weap/staff" : 5,
                ]));
    SetCanClose(1);
    SetClosed(0);

}
mixed CanGet(object ob) { return "The rack does not budge.";}
void init(){
    ::init();
}
