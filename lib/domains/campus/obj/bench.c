/*    /domains/campus/etc/stool.c
 *    From the Dead Souls Object Library
 *    An example of a chair object
 *    Created by Descartes of Borg 961221
 */

#include <lib.h>

inherit LIB_CHAIR;


protected void create() {
    chair::create();
    SetKeyName("bench");
    SetId("bench");
    SetAdjectives("wooden");
    SetShort("木长椅");
    SetLong("这是一把典型的木制长椅，就像你在公园里看到的那种。它显然是用来坐的。");
    SetMass(1500);
    SetDollarCost(15);
    SetMaxSitters(3);
}
mixed CanGet(object ob) { return "The bench does not budge.";}
void init(){
    ::init();
}
