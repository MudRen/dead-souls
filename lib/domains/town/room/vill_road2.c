#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("东村路");
    SetNightLong("你在一条长长的路上，由灯柱照亮。杂货店在北边。道路东西贯穿城镇。冒险者公会在南边。");
    SetDayLong("你在一条长长的路上。杂货店在北边。道路东西贯穿城镇。冒险者公会在南边。");
    SetItems( ([
                ({"adventurers guild","guild"}) : "路南边的这座小建筑是冒险者们——无论大小——来记录他们的功绩并寻求晋升的地方。",
                ({"shop","store","general store"}) : "这是杂货店，几乎任何东西都可以在这里买卖。",
                ({"road","long road"}) : "一条东西走向、贯穿城镇的鹅卵石路。",
                ]) );
    SetSkyDomain("town");
    AddTerrainType(T_ROAD);
    SetEnters( ([ 
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/shop",
                "south" : "/domains/town/room/adv_guild",
                "east" : "/domains/town/room/vill_road3",
                "west" : "/domains/town/room/start",
                ]) );
    AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    ::init();
}
