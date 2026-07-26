#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("slug");
    SetId( ({"gastropod"}) );
    SetAdjectives( ({"big", "thick", "slimy", "garden", "gross"}) );
    SetShort("一只黏糊糊的鼻涕虫");
    SetLong("一只又大又肥又黏的花园鼻涕虫。真恶心！");
    SetAutoStand(0);
    SetPosition(POSITION_LYING);
    SetLevel(1);
    SetMelee(1);
    SetRace("slug");
    SetMaxHealthPoints(5);
    SetGender("male");
}
void init(){
    ::init();
}
