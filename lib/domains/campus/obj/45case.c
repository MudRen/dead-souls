#include <lib.h>

inherit LIB_STORAGE;

void create() {
    storage::create();
    SetKeyName("cardboard case");
    SetAdjectives( ({"small", "cardboard", "45", "ammo", "ammunition"}) );
    SetId( ({ "case" }) );
    SetShort(".45口径弹药盒");
    SetLong("一个小纸板盒，设计用于携带.45口径ACP弹药。");
    SetMass(10);
    SetDollarCost(1);
    SetMaxCarry(12);
    SetInventory( ([
                "/domains/campus/obj/45round" : 12,
                ]) );
}

mixed CanReceive(object ob){
    if(ob->GetKeyName() != ".45 round") {
        write("This cardboard case is for .45 acp ammunition only.");
        return 0;
    }
    return storage::CanReceive(ob);
}

void init(){
    storage::init();
}
