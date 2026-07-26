/*    /domains/Ylsrim/etc/stool.c
 *    From the Dead Souls Mud Library
 *    An example of a chair object
 *    Created by Descartes of Borg 961221
 */

#include <lib.h>

inherit LIB_CHAIR;

protected void create() {
    chair::create();
    SetKeyName("stool");
    SetId("stool");
    SetAdjectives("wooden", "rickety");
    SetShort("一张摇晃的木凳");
    SetLong("这张凳子足够结实，你可以坐在上面。");
    SetMass(1500);
    SetValue(15);
    SetMaxSitters(1);
}
