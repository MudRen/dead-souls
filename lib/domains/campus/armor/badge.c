#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("visitor's pass");
    SetId(({"testchar badge","badge","pass","visitor's pass"}));
    SetShort("测试角色访客通行证");
    SetLong("这枚夹式塑料徽章可以让佩戴者进入一些通常只有管理员才能进入的区域。滥用此通行证将受到纪律处分。通行证底部有一行小字写着：点击鞋跟");
    SetMass(10);
    SetDollarCost(5000);
    SetDamagePoints(100);
    SetArmorType(A_AMULET);
    SetRetainOnDeath(1);
    SetRestrictLimbs( ({ "torso" }) );
}
void init(){
    ::init();
    add_action("nplh","click");
    add_action("post_it","post");
}
int nplh(string str){
    if(str=="heels"){
        if(present(this_object()->GetKeyName(),this_player() ) ){
            write("There's no place like home!\n"+
                    "You are transported by an awesome whirlwind somewhere "+
                    "else...\n");
            this_player()->eventMoveLiving("/domains/campus/room/start");
            return 1;
        }
        write("You click your heels together...but feel "+
                "as though you're missing something.\n");
        return 1;
    }
}
int post_it(string str){
    if(present("chalkboard",environment(this_player())) && !creatorp(this_player()) ){
        write("As a visitor, you are not allowed to post on creator boards.");
        return 1;
    }
}
string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " is an authorized Test Character.";
}
