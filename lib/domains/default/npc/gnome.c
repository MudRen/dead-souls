#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("gnome");
    SetAdjectives( ({"cute", "cuddly", "endearing"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一个可爱的小矮人");
    SetLong("这个可爱的生物很像矮人，只是更小更好相处。他长长的白胡子、富有感染力的笑声和闪闪发光的眼睛让你想起了很久以前认识并爱过的一个人。他的圆锥形帽子和老式、 awkward 的穿着方式让他更加可爱。你只想拥抱他，把他放在你的花园里。");
    SetLevel(1);
    SetMelee(1);
    SetRace("gnome");
    SetGender("male");
}
void init(){
    ::init();
}
