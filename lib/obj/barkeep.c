#include <lib.h>

inherit LIB_BARKEEP;

protected void create() {
    barkeep::create();
    SetKeyName("barkeep");
    SetId( ({ "barman" }) );
    SetShort("普通酒保");
    SetLevel(1);
    SetLong("一个不起眼的人，工作是出售食物和饮料。");
    SetMenuItems(([
                ]));
    SetGender("male");
    SetRace("human");
    SetSkill("bargaining", 1);
    SetProperty("no bump", 1);
    SetLocalCurrency("silver");
}
void init(){
    ::init();
}
