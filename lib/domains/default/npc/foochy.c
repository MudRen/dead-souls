#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("foochy");
    SetAdjectives( ({"overpampered", "ridiculous", "little", "toy", "toylike"}) );
    SetId(({"npc","mob","character","mobile","poodle"}));
    SetShort("粉色贵宾犬 Foochy");
    SetLong("一只相当可笑、明显被过度宠爱的小玩具狗。");
    SetLevel(1);
    SetMelee(1);
    SetRace("dog");
    SetGender("female");
}
void init(){
    ::init();
}
