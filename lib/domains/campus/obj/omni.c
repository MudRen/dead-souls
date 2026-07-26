#include <lib.h>
#include ROOMS_H
inherit LIB_ITEM;
inherit LIB_PRESS;

int check_environs();
int vanish_count = 50;
protected void create() {
    item::create();
    SetKeyName("omni");
    SetId(({"omni","Omni","device"}));
    SetShort("万能遥控器");
    SetLong("这是一个小型圆形金属装置，铜色，外观类似于怀表。顶部小金属按钮旁边有一个闪烁的红灯。");
    SetMass(10);
    SetDollarCost(300);
    AddItem("button", "万能遥控器上的一个按钮。");
}
void init() {
    ::init();
    check_environs();
}
mixed CanPress(object who, string target) {
    if(!present(this_object()->GetKeyName(),who ) && target == "button"){
        return "你没有万能遥控器！";
    }
    if(this_object()->GetId() == target){
        return "你不能按那个。";
    }
    return 1;
}
mixed eventPress(object who, string where) {
    object *rooms = objects( (: inherits(LIB_ROOM, $1) :) );
    object target;
    int success = 0;
    rooms = filter(rooms, (: member_array(base_name($1), ({ ROOM_START,
                        ROOM_FURNACE, ROOM_VOID, ROOM_POD, ROOM_DEATH, ROOM_WIZ,
                        ROOM_ARCH, ROOM_NETWORK, ROOM_ROUTER, LIB_FURNACE,  
                        ROOM_FREEZER }) ) == -1  && strsrch(base_name($1),"/realms/") &&
                !inherits(LIB_FURNACE,$1) && 
                !($1->GetVirtual() && !grepp(base_name($1),",")) &&
                last_string_element(base_name($1),"/") != "death" :) );
    say(who->GetName()+"变成了"+dbz_colors("multicolored")+"然后消失了！");
    write("你感到一阵短暂的眩晕，发现自己已经身在别处！");
    while(!success){
        target = rooms[random(sizeof(rooms)-1)];
        success = who->eventMove(target);
    }
    who->eventDescribeEnvironment();
    tell_room(target, "伴随着一道彩色闪光，"+who->GetName()+
            "出现了！",who);
    return 1;
}

void heart_beat(){
    object env = environment();
    object *holders;
    if(!env) return;
    holders = filter(containers(this_object()),
            (: interactive($1) :) );
    if(interactive(env)) vanish_count--;
    else if(sizeof(holders) && random(100) > 80) vanish_count--;
    if(vanish_count < 0){
        tell_object(env,"万能遥控器发出耀眼的光芒后消失了！");
        this_object()->eventDestruct();
    }
    if(vanish_count == 5){
        tell_object(env,"万能遥控器开始发出暗红色的光芒。");
        this_object()->SetLong("这是一个小型圆形金属装置，铜色，外观类似于怀表。顶部小金属按钮旁边有一个闪烁的红灯。它正发出暗红色的光芒。");
        this_object()->SetShort("万能遥控器（发光中）");
    }
}

int check_environs(){
    if( interactive(environment()) ){
        set_heart_beat(10);
        return 1;
    }
    return 1;
}
