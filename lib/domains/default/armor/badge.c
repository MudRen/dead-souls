#include <lib.h>
#include ROOMS_H
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("visitor pass");
    SetId(({"testchar badge","badge","pass","visitor's pass"}));
    SetShort("一个测试角色访客通行证");
    SetLong("这个 clip-on plastic badge grants the wearer access to some areas typically restricted to creator staff only。滥用此 pass is grounds for disciplinary action。 A small scribble at the bottom of the pass reads: click heels");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetMass(10);
    SetBaseCost(5000);
    SetDamagePoints(100);
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
            write("没有哪里比得上家！\n"+
                    "你被一阵 awesome whirlwind 传送到了别处...\n");
            this_player()->eventMoveLiving(ROOM_START);
            return 1;
        }
        write("你 clicking your heels together... but feel as though you're missing something。\n");
        return 1;
    }
}
string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " is an authorized Test Character.";
}
