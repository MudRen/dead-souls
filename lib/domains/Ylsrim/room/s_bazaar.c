/*    /domains/Ylsrim/room/s_bazaar.c
 *    From the Dead Souls Mud Library
 *    A simple room example with a unique, wandering NPC
 *    Created by Descartes of Borg 960302
 */

#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("Ylsrim");
    SetClimate("arid");
    SetAmbientLight(30);
    SetShort("伊尔斯利姆集市南端");
    SetLong("沿着伊尔斯利姆集市的南端，矗立着一家餐厅和一家酒馆。"
            "集市的中心区域就在北边。");
    SetSkyDomain("town");
    SetInventory(([
                "/domains/Ylsrim/npc/traveler" : 1,
                ]));
    AddItem("pub", "你可以从伊尔斯利姆最受尊敬的居民之一那里买一杯麦酒。", ({ "lars" }));
    AddItem("restaurant", "这家餐厅以炖菜闻名。",
            ({ "toral" }));
    SetExits( ([ "north" : "/domains/Ylsrim/room/"+ "bazaar" ]) );
    SetEnters( ([ 
                "pub" : "/domains/Ylsrim/room/"+ "pub" ]) );
}
void init(){
    ::init();
}
