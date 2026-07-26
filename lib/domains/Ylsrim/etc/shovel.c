/*    /domains/Ylsrim/etc/shovel.c
 *    From the Dead Souls Mud Library
 *    An example of how to code a digging tool
 *    Created by Descartes of Borg 961231
 */

#include <lib.h>

inherit LIB_ITEM;
inherit LIB_DIG_WITH;

protected void create() {
    item::create();
    SetKeyName("shovel");
    SetId("shovel", "spade");
    SetAdjectives("wooden");
    SetShort("一把铲子");
    SetLong("一把普通的木铲。你大概可以用它来挖掘。");
    SetMass(87);
    SetValue(50);
}
void init(){
    ::init();
}
