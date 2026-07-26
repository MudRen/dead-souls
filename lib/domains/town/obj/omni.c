#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
inherit LIB_PRESS;
int check_environs();
int vanish_count;
protected void create() {
    item::create();
    SetKeyName("omni");
    SetId(({"omni","Omni","device"}));
    SetShort("一把万能钥匙");
    SetLong("这是一个小而圆的金属设备，铜色，上面有一些奇怪的符文。它似乎能打开任何锁。");
    SetMass(10);
    SetBaseCost("silver",300);
    AddItem("button", "万能钥匙上的一个按钮。");
    SetVendorType(VT_MAGIC);
}

void init() {
    vanish_count=7200;
    check_environs();
}
mixed CanPress(object who, string target) {
    if(!present(this_object()->GetKeyName(),who ) && target == "button"){
        return "你没有万能钥匙！";
    }
    if(this_object()->GetId() == target){
        return "你不能推那个。";
    }
    return 1;
}
mixed eventPress(object who, string target) {
    say(this_player()->GetName()+"变成了彩色然后消失了。\n");
    write("你感到一阵眩晕，发现自己回到了酒馆。\n");
    this_player()->eventMoveLiving("/domains/town/room/tavern");
    return 1;
}
void heart_beat(){
    vanish_count--;
    if(vanish_count < 0){
        tell_object(environment(),"万能钥匙发出耀眼的光芒然后消失了！");
        this_object()->eventDestruct();
    }
    if(vanish_count == 50){
        tell_object(environment(),"万能钥匙开始发出暗红色的光芒。");
        this_object()->SetLong("这是一个小而圆的金属设备，铜色，外观类似怀表。顶部的小金属按钮旁边有一个闪烁的红灯。它正发出暗红色的光芒。");
        this_object()->SetShort("一把万能钥匙（发光中）");
    }
}
int check_environs(){
    if( interactive(environment()) ){
        set_heart_beat(1);
        return 1;
    }
    return 1;
}
