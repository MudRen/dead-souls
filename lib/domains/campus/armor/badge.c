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
            write("没有什么地方比得上家！\n"+
                    "你被一阵奇妙的旋风传送到了其他地方……\n");
            this_player()->eventMoveLiving("/domains/campus/room/start");
            return 1;
        }
        write("你把鞋跟碰在一起……但感觉好像少了什么东西。\n");
        return 1;
    }
}
int post_it(string str){
    if(present("chalkboard",environment(this_player())) && !creatorp(this_player()) ){
        write("作为访客，你不能在创造者公告板上发帖。");
        return 1;
    }
}
string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + " 是一位授权的测试角色。";
}
