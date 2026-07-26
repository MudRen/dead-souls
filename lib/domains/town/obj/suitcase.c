#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("wardrobe");
    SetId(({"wardrobe"}));
    SetAdjectives(({"wood","tall"}));
    SetShort("一个高大的木制衣柜");
    SetLong("这件家具设计用来存放衣物和其他物品。");
    SetMass(2000);
    SetBaseCost("silver",150);
    SetMaxCarry(2000);
    SetInventory(([
                "/domains/town/armor/long_boot_l": 1,
                "/domains/town/armor/long_boot_r": 1,
                "/domains/town/armor/belt": 1,
                "/domains/town/armor/vest": 1,
                "/domains/town/armor/goggles": 1,
                "/domains/town/armor/hunting_cap": 1,
                "/domains/town/armor/glove_r": 1,
                "/domains/town/armor/glove_l": 1,
                "/domains/town/armor/bearsuit": 1,
                "/domains/town/armor/overcoat": 1,
                "/domains/town/armor/jacket": 1,
                "/domains/town/armor/jeans": 1,
                "/domains/town/armor/shirt": 1,
                "/domains/town/armor/scarf": 1,
                ]));
    SetCanClose(1);
    SetClosed(1);
    AddMoney("silver",100);
}

void init(){
    ::init();
}
