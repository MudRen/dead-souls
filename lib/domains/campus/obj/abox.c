/*    /domains/Examples/etc/bag.c
 *    from the Dead Souls LPC Library
 *    a sample bag object
 *    created by Descartes of Borg 950529
 */

#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("ammunition box");
    SetId(({"can","box"}));
    SetAdjectives(({"metal","ammo","ammunition","large"}));
    SetShort("弹药箱");
    SetLong("这是一个大型金属箱，装有各种弹药。");
    SetMass(200);
    SetDollarCost(50);
    SetMaxCarry(5000);
    SetCanClose(1);
    SetClosed(0);

    SetInventory( ([
                "/domains/campus/obj/9mmclip": 10,
                "/domains/campus/obj/223clip": 10,
                "/domains/campus/obj/357case": 10
                ]) );

}

void init(){
    ::init();
}

mixed CanGet(object ob) { return "The metal ammunition box does not budge.";}
