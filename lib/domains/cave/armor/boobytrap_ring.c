/*
 * Note that this ring, unlike the boobytrapped dagger, does
 * not check to see if it has been previously armed. This prevents
 * a player from disarming the ring by simply logging out
 * and logging back in.
 */

#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <boobytraps.h>

inherit LIB_ARMOR;

void boobytrap_me(){
    object shadowtrap;
    if(!clonep(this_object())) return; /* Avoids boobytrapping the blueprint ob */

    shadowtrap = new("/shadows/needle_trap2");
    shadowtrap->SetTrapDescription("A poison needle trap.");
    shadowtrap->SetTrapLevel(50);
    shadowtrap->SetAutoResets(0);
    shadowtrap->SetTrapType(BOOBYTRAP_WEAR);
    shadowtrap->eventShadow(this_object());
}

protected void create(){
    armor::create();
    SetKeyName("silver_ring");
    SetId(({"ring","silver ring"}));
    SetAdjectives( ({"beautiful"}) );
    SetShort("一枚美丽的银戒指");
    SetLong("这是一枚简单而美丽的银戒指，适合戴在手指上。戒指上刻有铭文。");
    SetMass(1);
    SetBaseCost("silver",500);
    SetArmorType(A_RING);
    SetItems(([
                ({"script","words","inscription","writing"}) : "戒指上刻有高度风格化的文字。"
                ]) );
    SetRead(({"script","words","inscription","writing"}), "\"bad wolf\""  );
    boobytrap_me();
}

void init(){
    ::init();
}
