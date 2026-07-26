#include <lib.h>
#include ROOMS_H
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("visitor pass");
    SetId(({"testchar badge","badge","pass","visitor's pass"}));
    SetShort("一张测试角色访客通行证");
    SetLong("这个塑料别针徽章赋予佩戴者进入某些区域的权限。上面写着"访客通行证"。");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetMass(1);
    SetBaseCost("silver",500);
    SetArmorType(A_AMULET);
    SetRetainOnDeath(1);
    SetRestrictLimbs( ({ "torso" }) );
}

void init(){
    ::init();
    add_action("nplh","click");
}

int nplh(string str){
    if(str=="heels"){
        if(present(this_object()->GetKeyName(),this_player() ) ){
            write("There's no place like home!\n"+
                    "You are transported by an awesome whirlwind somewhere "+
                    "else...\n");
            this_player()->eventMoveLiving(ROOM_START);
            return 1;
        }
        write("You click your heels together...but feel "+
                "as though you're missing something.\n");
        return 1;
    }
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " is an authorized Test Character.";
}
