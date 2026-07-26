#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("identification badge");
    SetId(({"badge","pass","id","i.d.","pass of dr kleiner"}));
    SetAdjectives( ({"clip on", "plastic", "id","i.d.","access","kleiner"}) );
    SetShort("身份徽章");
    SetLong("这枚夹式塑料徽章可以让持有者进入限制区域。上面有一张照片和一些文字。");
    SetMass(10);
    SetDollarCost(5);
    SetDamagePoints(100);
    SetArmorType(A_AMULET);
    SetRestrictLimbs( ({ "torso" }) );
    SetReads( ([
                "default" : "Isaac Kleiner, Ph.D.",
                "writing" : "Isaac Kleiner, Ph.D.",
                ]) );
    SetItems( ([
                ({"photo","picture","photograph"}) : "An older, white-haired "+
                "gentleman, wearing an affable, goofy grin.",
                ]) );
}
void init(){
    ::init();
}
