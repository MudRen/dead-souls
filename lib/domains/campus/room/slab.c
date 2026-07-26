#include <lib.h>
#include <daemons.h>

inherit LIB_ROOM;

int SignRead(){
    string list;
    list = implode(keys(STARGATE_D->GetStargates()),", ");
    write("以下是星门操作说明。");
    write("死亡之灵魂星门系统提供星门网络内的传送功能。要使用星门网络，找到一个空闲的星门，然后拨号另一个已知星门的名称。然后进入出站星门，如果一切顺利，就会传送到拨号的星门。要前往Uruk（如果那是一个有效的星门名称），你需要：dial uruk\n"
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
    SetShort("科学楼星门实验室");
    SetLong("这个大房间是新发现的星门技术的测试场地，该技术允许在遥远位置之间进行瞬间传送。科学楼主走廊在南边。\n%^BOLD%^%^GREEN%^这里有一块说明牌。%^RESET%^");
    SetItems(([
                ({ "sign", "instruction sign", "instructions sign", "instruction", "instructions" }) : "一块可以阅读的告示牌。看起来是星门操作说明。",
                ]));
    SetInventory(([
                "/domains/campus/obj/stargate" : 1,
                "/domains/campus/npc/kleiner" : 1,
                ]));
    SetExits(([
                "south" : "/domains/campus/room/science2",
                ]));
    SetRead("sign", (: SignRead() :) );
}
int CanReceive(object ob) {
    if(!ob) return 0;
    return room::CanReceive(ob);
}

void init(){
    ::init();
}
