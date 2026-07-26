#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("疾病实验室准备室");
    SetLong("这个房间的设计目的是防止在楼下房间测试的疾病传播。你还可以在这里获得防疾病项圈，这样你就可以在隔离区工作而不会被感染。要感染测试对象，请使用医疗三录仪。要让他们全部恢复健康，请输入'update'，这将重置房间。测试对象正在楼下等你。");
    SetExits( ([
                "south" : "/domains/default/room/wiz_corr1",
                "down" : "/domains/default/room/quarantine2.c",
                ]) );
    SetInventory(([
                "/domains/default/obj/collarchest" : 1,
                ]));

    SetProperty("no attack", 1);

}
int CanReceive(object ob) {
    object *inv;
    string taxonomy;

    if(inherits(LIB_GERM,ob)) return 0;

    inv = deep_inventory(ob);
    foreach(object thing in inv){
        if(inherits(LIB_GERM,thing)) {
            write("%^YELLOW%^在你身上发现了一个寄生虫！正在自动清除。%^RESET%^");
            if(taxonomy = thing->GetGermName()) write("%^YELLOW%^正在清除："+taxonomy+"。%^RESET%^");
            thing->eventMove(ROOM_FURNACE);
        }
    }

    return room::CanReceive();
}

void init(){
    ::init();
}
