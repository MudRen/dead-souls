/*    /domains/Ylsrim/fish/shark.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <dirs.h>
#include <damage_types.h>

inherit LIB_FISH;

void BiteMe(object who);

protected void create() {
    fish::create();
    SetKeyName("blue shark");
    SetId( ({ "shark", "blue shark" }) );
    SetShort("一条蓝鲨");
    SetLong("这是一条巨大的长鱼，有着锋利的牙齿和肉食性的胃口。");
    SetMass(100); 
    SetFight(40);
    SetFood("/domains/Ylsrim"+ "/meal/shark");
}

int eventCatch(object who, object pole) { 
    call_out((: BiteMe, who :), 0);
    return 1;
}

void BiteMe(object who) {
    who->eventPrint("鲨鱼在死前咬了你一口！");
    environment(who)->eventPrint("鲨鱼在死前咬了" + who->GetName() + "一口！", who);
    who->eventReceiveDamage(this_object(), KNIFE, random(20), 0,
            who->GetRandomLimb("right hand"));
}
