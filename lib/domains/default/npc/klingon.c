#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("klingon");
    SetAdjectives( ({"klingon", "adolescent", "unpredictable"}) );
    SetId( ({"warrior", "fighter", "adolescent"}) );
    SetShort("一个青少年克林贡人");
    SetLong("有时比成年克林贡人更危险，青少年有东西需要证明，在攻击性方面可能难以预测。这个有着D'Ghor家族独特的脊状突起，这让他更加渴望证明自己作为战士的价值。");
    SetClass("fighter");
    SetLevel(5);
    SetMelee(1);
    SetRace("klingon");
    SetGender("male");
}
void init(){
    ::init();
}
