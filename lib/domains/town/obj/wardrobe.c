#include <lib.h>

inherit LIB_STORAGE;

mixed direct_enter_obj(){
    return 1;
} 
mixed direct_enter_into_obj(){
    return direct_enter_obj();
}

int eventEnter(object who){
    int ret;

    if(GetClosed()){
        write("你撞到了衣柜关着的门。");
        say(this_player()->GetName()+"撞到了衣柜。");
        return 0;
    }

    ret = who->eventMoveLiving("/domains/town/room/secret",
            "$N enters the wardrobe.", "$N arrives from the bedroom west.");

    if(!ret){
        write("你没能进去。");
        return 0;
    }
    return 1;
}

void create() {
    ::create();
    SetKeyName("wardrobe");
    SetId(({"wardrobe"}));
    SetAdjectives(({"wood","tall"}));
    SetShort("一个高大的木制衣柜");
    SetLong("这件家具设计用来存放衣物和其他物品。");
    SetMass(2000);
    SetMaxCarry(2000);
    SetInventory(([
                "/domains/town/armor/long_boot_l" : 1,
                "/domains/town/armor/bearsuit" : 1,
                "/domains/town/armor/scarf" : 1,
                "/domains/town/armor/belt" : 1,
                "/domains/town/armor/goggles" : 1,
                "/domains/town/armor/shirt" : 1,
                "/domains/town/armor/jeans" : 1,
                "/domains/town/armor/hunting_cap" : 1,
                "/domains/town/armor/vest" : 1,
                "/domains/town/armor/long_boot_r" : 1,
                "/domains/town/armor/jacket" : 1,
                "/domains/town/armor/overcoat" : 1,
                ]));
    SetBaseCost("silver",150);
    SetCanClose(1);
    SetClosed(1);
    AddMoney("silver",100);
    SetPreventGet("衣柜纹丝不动。");
}

void init(){
    ::init();
}
