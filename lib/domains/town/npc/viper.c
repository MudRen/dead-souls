#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("viper");
    SetAdjectives( ({"dangerous", "venomous", "pit"}) );
    SetId( ({"snake", "reptile"}) );
    SetShort("一条蝮蛇");
    SetLong("这是一条体型粗壮的蛇，约三英尺长，肌肉发达的身体上有棕色和黑色的花纹。它是蝰蛇科的成员，这是一类以毒液致命性而闻名的蛇。");
    SetAutoStand(0);
    SetPosition(POSITION_LYING);
    SetLevel(3);
    SetMelee(1);
    SetRace("viper");
    SetGender("male");
}
void init(){
    ::init();
}
