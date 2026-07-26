#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("sheep");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一只羊");
    SetLong("这是一种典型的温顺哺乳动物有蹄类，喜欢在田野里漫步吃草。它的皮毛被称为羊毛，异常浓密且温暖。羊毛被珍视为服装的组成部分。");
    SetLevel(1);
    SetMelee(1);
    SetRace("sheep");
    SetGender("male");
}
void init(){
    ::init();
}
