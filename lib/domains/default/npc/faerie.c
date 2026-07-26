#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("faerie");
    SetAdjectives( ({"fragile", "beautiful", "incredibly beautiful", "insubstantial", "tiny"}) );
    SetId( ({"fairy", "fairie"}) );
    SetShort("一个小巧精致的仙女");
    SetLong("这种生物看起来像一个微小的人类，大约六英寸高，有着透明的翅膀。它看起来 fragile and insubstantial，同时也 incredibly beautiful。");
    SetPosition(POSITION_FLYING);
    SetLevel(1);
    SetMelee(1);
    SetRace("faerie");
    SetMaxHealthPoints(50);
    SetGender("female");
}
void init(){
    ::init();
}
