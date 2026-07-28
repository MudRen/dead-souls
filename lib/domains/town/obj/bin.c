#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bin");
    SetAdjectives( ({"newbie", "charity", "freebie"}) );
    SetId( ({"newbie bin"}) );
    SetShort("新手物品箱");
    SetLong("这个中等大小的箱子用来存放可能对新手有用的物品。默认包含一些不值钱的东西，但鼓励玩家慷慨捐献以帮助较弱的玩家。查看内容：look in bin");
    SetInventory(([
                "/domains/town/obj/slip_heal" : 1,
                "/domains/town/obj/match" : 5,
                "/domains/town/obj/slip_regenerate" : 1,
                "/domains/town/obj/slip_excise" : 3,
                "/domains/town/obj/rayovac" : 1,
                "/domains/town/obj/spam" : 1,
                "/domains/town/obj/dcell" : 2,
                "/domains/town/obj/torch" : 1,
                ]));
    SetMaxCarry(3500);
    SetNoCondition(1);
    SetCanClose(0);
    SetMass(100);
    SetBaseCost("silver",1);
    SetNoClean(1);
}

void init(){
    ::init();
}

mixed CanGet(object ob) { return "桶纹丝不动。";}
