#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("竞技场");
    SetLong("你在一个有着空白水泥墙的大房间里。这个房间的建造目的是让创造者们可以测试他们的盔甲、武器和NPC的战斗能力。这里有一扇大钢门，可以用来防止弱小的生物逃跑。");
    SetItems( ([
                ({"wall","walls"}) : "墙壁是光滑的水泥墙。",
                ({"floor","ceiling"}) : "地板和天花板与墙壁一样，都是由光滑的水泥制成的。" ]) );
    SetInventory(([
                "/domains/default/npc/fighter" : 1,
                "/domains/default/obj/locker" : 1,
                "/domains/default/npc/dummy" : 1,
                "/domains/default/obj/case" : 1,
                "/domains/default/obj/abox" : 1,
                "/domains/default/obj/javelin_bin" : 1,
                "/domains/default/obj/rack" : 1,
                ]));
    SetExits( ([ 
                "south" : "/domains/default/room/wiz_corr_east",
                ]) );
    SetPlayerKill(1);

    SetDoor("south", "/domains/default/doors/steel_door2.c");

}

int CanReceive(object sneak) {
    object *living_stack = get_livings(sneak);
    if(!living_stack || !arrayp(living_stack)) living_stack = ({ sneak });
    foreach(object ob in living_stack){
        if(playerp(ob) && !creatorp(ob) &&
                !member_group(ob,"TEST")) {
            message("info","仅限创造者工作人员使用，抱歉。", ob);
            return 0;
        }
    }
    return 1;
}

void init(){
    ::init();
}
