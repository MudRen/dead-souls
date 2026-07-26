#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("萨奎沃路");
    SetLong("这是一条鹅卵石路，向北通往城镇。魔法商店在西边。\n%^GREEN%^路边有一口古老的水井。%^RESET%^");
    SetItems( ([
                ({"well","old well","dry well"}) : "这看起来像是城镇实施更现代的供水系统之前使用的那种取水设施。看起来早已干涸并被废弃。",
                "bank" : "村庄第一银行",
                ({"road","cobblestone road"}) : "一条南北走向的鹅卵石路。"
                ]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "north" : "/domains/town/room/start",
                "west" : "/domains/town/room/magic_shop",
                ]) );
    if(strsrch(mud_name(), "Dead Souls")){
        //AddExit("south", "/domains/campus/room/south_road2");
    }
    AddTerrainType(T_ROAD);
    SetNoModify(0);
    SetEnters( ([
                "well" : "/domains/town/room/well1"
                ]) );
    AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    room::init();
}
