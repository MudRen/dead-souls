#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("ogre");
    SetAdjectives( ({"foul", "stinking", "unlovable", "potbellied", "snaggletoothed", "monstrous"}) );
    SetId( ({"oaf", "beast"}) );
    SetShort("一个可怕的食人魔");
    SetLong("这不是一个可爱的傻瓜。这个恶臭的野兽是人类的两倍高，大腹便便，牙齿参差不齐。它的皮肤上爬满了寄生虫，并覆盖着干燥的体液。");
    SetLevel(1);
    SetMelee(1);
    SetRace("ogre");
    SetGender("male");
}
void init(){
    ::init();
}
