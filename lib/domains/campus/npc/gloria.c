#include <lib.h>
#include <vendor_types.h>

inherit LIB_BARKEEP;

protected void create() {
    barkeep::create();
    SetKeyName("gloria");
    SetId(({"woman","worker","gloria","lady","lunch lady"}));
    SetShort("格洛丽亚，午餐阿姨");
    SetLong("格洛丽亚是一个身材矮小、看起来疲惫的女人，年纪不小了。她看起来不太高兴……事实上，她看起来很暴躁。也许你问她的话，她会卖给你菜单上的东西。但也可能不会。");
    SetInventory(([
                "/domains/campus/armor/collar" : "wear collar on neck",
                "/domains/campus/obj/spam" : 1,
                "/domains/campus/armor/foodsmock" : "wear smock",
                ]));
    SetMenuItems(([
                ({ "sandwich", "ham sandwich" }) : "/domains/campus/meals/ham_sand",
                ({ "burger", "hamburger" }) : "/domains/campus/meals/burger",
                ({ "salad", "salad of the day" }) : "/domains/campus/meals/salad",
                ({ "milk", "carton of milk" }) : "/domains/campus/meals/milk",
                ({ "gatorade", "sports drink" }) : "/domains/campus/meals/gator",
                ]));
    SetLevel(1);
    SetRace("human");
    SetSkill("bargaining", 1);
    SetGender("female");
    SetLocalCurrency("dollars");
}
void init(){
    ::init();
}
