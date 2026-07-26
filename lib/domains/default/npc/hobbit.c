#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("hobbit");
    SetAdjectives( ({"saucy", "saucy looking", "stout", "somewhat stout", "capable"}) );
    SetId( ({"lass", "adventurer"}) );
    SetShort("一个霍比特人");
    SetLong("大约三英尺高，有些矮胖，眼睛里闪烁着快乐的光芒，这个看起来活泼的霍比特少女看起来和任何冒险者一样能干。");
    SetLevel(1);
    SetMelee(1);
    SetRace("hobbit");
    SetGender("female");
}
void init(){
    ::init();
}
