#include <lib.h>

inherit LIB_STORAGE;

void create() {
    storage::create();
    SetKeyName("cardboard case");
    SetAdjectives( ({"small", "cardboard", "357", "ammo"}) );
    SetId( ({ "case" }) );
    SetShort(".357口径弹药盒");
    SetLong("一个小纸板盒，设计用于携带.357口径弹药。");
    SetMass(10);
    SetDollarCost(1);
    SetMaxCarry(12);
}

mixed CanReceive(object ob){
    if(ob->GetKeyName() != ".357 round") {
        tell_object(this_player(),"这个纸板盒只能装.357口径弹药。");
        return 0;
    }
    return storage::CanReceive(ob);
}

void init(){
    storage::init();
}
