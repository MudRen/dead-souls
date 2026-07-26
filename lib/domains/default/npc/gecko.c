#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("gecko");
    SetAdjectives( ({"gecko", "green", "small"}) );
    SetId( ({"lizard"}) );
    SetShort("一只壁虎");
    SetLong("这是一只小蜥蜴，大约四英寸长。它有绿色的皮肤和异常大的眼睛。");
    SetWimpy(80);
    SetLevel(1);
    SetMelee(1);
    SetRace("lizard");
    SetMaxHealthPoints(10);
    SetGender("male");
}
void init(){
    ::init();
}
