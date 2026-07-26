#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("gnoll");
    SetAdjectives( ({"filthy", "horrendous"}) );
    SetId( ({"dogman", "dog-man", "dog man"}) );
    SetShort("一个肮脏的大型狗头人");
    SetLong("这似乎是人类和鬣狗之间的可怕杂交。它缠结的皮毛上沾满了血和粪便，它流着口水的下巴似乎永远不会停止滴口水。");
    SetLevel(1);
    SetMelee(1);
    SetRace("gnoll");
    SetGender("male");
}
void init(){
    ::init();
}
