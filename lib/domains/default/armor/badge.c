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
    SetLong("这个塑料别针徽章可以让佩戴者进入一些通常只限于创造者工作人员的区域。滥用此通行证将受到纪律处分。通行证底部有一行小字：点击鞋跟");
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
                    "你被一阵强大的旋风传送到了别处...\n");
            this_player()->eventMoveLiving(ROOM_START);
            return 1;
        }
        write("你点击鞋跟...但感觉好像缺少了什么东西。\n");
        return 1;
    }
}
string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " 是一个授权的测试角色。";
}
