/*    /domains/Examples/etc/bag.c
 *    from the Nightmare IV LPC Library
 *    a sample bag object
 *    created by Descartes of Borg 950529
 */

#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("chest");
    SetId(({"chest"}));
    SetAdjectives(({"medical","metal","stainless","steel"}));
    SetShort("一个不锈钢箱子");
    SetLong("这是一个用于存放医疗工具的箱子。");
    SetMass(274);
    SetDollarCost(50);
    SetMaxCarry(500);
    SetPreventPut("你不能把这个放进去！");
    SetInventory(([
                "/secure/obj/medtric" : 1,
                "/domains/default/armor/collar" : 5,
                ]) );
    SetCanClose(1);
    SetClosed(1);
}
mixed CanGet(object ob) { return "箱子纹丝不动。";}
