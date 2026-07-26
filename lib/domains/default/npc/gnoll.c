#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("gnoll");
    SetAdjectives( ({"filthy", "horrendous"}) );
    SetId( ({"dogman", "dog-man", "dog man"}) );
    SetShort("一个肮脏的大型狗头人");
    SetLong("这似乎是 humanoid 和 hyena 之间的可怕杂交。它的 matted fur 上沾满了 blood and feces，它的 slavering jaws 似乎 never to stop dripping saliva。");
    SetLevel(1);
    SetMelee(1);
    SetRace("gnoll");
    SetGender("male");
}
void init(){
    ::init();
}
