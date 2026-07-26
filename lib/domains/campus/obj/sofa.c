/*    /domains/campus/etc/stool.c
 *    From the Dead Souls Object Library
 *    An example of a chair object
 *    Created by Descartes of Borg 961221
 */

#include <lib.h>

inherit LIB_CHAIR;


protected void create() {
    chair::create();
    SetKeyName("sofa");
    SetId("sofa");
    SetAdjectives( ({ "black", "small", "tasteful", "upholstered" }) );
    SetShort("沙发");
    SetLong("这是一张小型豪华沙发，黑色装饰品味高雅。它显然是用来坐的。");
    SetMass(1500);
    SetDollarCost(15);
    SetMaxSitters(2);
}
mixed CanGet(object ob) { return "The bench does not budge.";}
void init(){
    ::init();
}
