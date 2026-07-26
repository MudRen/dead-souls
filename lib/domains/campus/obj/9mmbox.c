#include <lib.h>

inherit LIB_STORAGE;

void create() {
    storage::create();
    SetKeyName("cardboard case");
    SetId(({"case","box"}));
    SetAdjectives(({"small", "cardboard", "9mm", "9 millimeter", "ammo"}));
    SetShort("9毫米弹药盒");
    SetLong("一个小纸板盒，设计用于携带9毫米弹药。");
    SetMass(10);
    SetDollarCost(1);
    SetMaxCarry(36);
    SetCanClose(1);
    SetClosed(0);
    SetInventory( ([
                "/domains/campus/obj/9mmround": 30
                ]) );
}

mixed CanReceive(object ob){
    if(ob->GetKeyName() != "9mm round") {
        tell_object(this_player(),"这个纸板盒只能装9毫米弹药。");
        return 0;
    }
    return storage::CanReceive(ob);
}

void init(){
    storage::init();
}
