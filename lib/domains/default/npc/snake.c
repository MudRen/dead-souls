#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("snake");
    SetId( ({"garter snake", "reptile"}) );
    SetAdjectives( ({"small", "harmless", "garter", "black", "black and yellow", "yellow and black"}) );
    SetShort("一条束带蛇");
    SetLong("这是一种小型无害的爬行动物，大约9英寸长。它是黑色的，身上有几条黄色条纹。这条蛇喜欢吃花园害虫。");
    SetAutoStand(0);
    SetPosition(POSITION_LYING);
    SetLevel(1);
    SetMelee(1);
    SetRace("snake");
    SetGender("male");
}
void init(){
    ::init();
}
