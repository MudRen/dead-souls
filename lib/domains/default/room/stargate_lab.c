#include <lib.h>
#include <daemons.h>

inherit LIB_ROOM;

int SignRead(){
    string list;
    list = implode(keys(STARGATE_D->GetStargates()),", ");
    write("这些是星门操作说明。");
    write("Dead Souls星门系统提供星门网络内的传送功能。要使用星门网络，首先找到一个空闲的星门，然后拨号另一个已知星门的名称。然后进入出站星门，如果一切顺利，就会传送到拨号的星门。要前往Uruk（如果那是一个有效的星门名称），你需要：dial uruk\n"
            "星门激活后：enter stargate");
    write("当前可用的星门有：");
    write("%^BOLD%^%^YELLOW%^"+list+"%^RESET%^");
    return 1;
}

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("星门实验室");
    SetLong("这是Dead Souls新型星门系统的测试实验室。\n"
            "%^BOLD%^%^GREEN%^这里有一个说明指示牌。%^RESET%^");
    SetItems(([
                ({ "sign", "instruction sign", "instructions sign", "instruction", "instructions" }) : "一个你可以阅读的指示牌。上面似乎是操作星门的说明。",
                ]));
    SetExits( ([
                "north" : "/domains/default/room/wiz_corr_east2.c",
                ]) );
    SetInventory(([
                "/domains/default/obj/stargate" : 1,
                ]));
    SetRead("sign", (: SignRead() :) );
    SetProperty("no attack", 1);

}
int CanReceive(object ob) {
    return room::CanReceive();
}

void init(){
    ::init();
}
