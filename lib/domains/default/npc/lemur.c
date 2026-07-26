#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("lemur");
    SetAdjectives( ({"small", "startling", "grey", "gray"}) );
    SetId( ({"primate", "simian"}) );
    SetShort("一只狐猴");
    SetLong("这只小动物的 appearance is startling。它看起来 much like a cross between a small monkey and a raccoon。它有 an elongated snout and the fur around its eyes is dark, like the mask of a bandit。 Yet its body is clearly simian, with the prehensile front limbs of a monkey。 Its grey, furry body ends in a ridiculously long tail that is striped white and black。");
    SetLevel(1);
    SetMelee(1);
    SetRace("primate");
    SetMaxHealthPoints(40);
    SetGender("male");
}
void init(){
    ::init();
}
