#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("市政厅");
    SetLong("这是村庄市政厅朴素的门厅。说真的，这里很简单，与小镇朴实的精神相符。书记官和公证人的办公室在北边，镇长的办公室在楼上。村庄道路在南边，选民登记处在东北方。");
    SetProperties (([
                "no attack":1, 
                "no bump":1, 
                "no steal":0, 
                "no magic":0, 
                "no paralyze":0, 
                "no teleport":0]));
    SetItems(([]));
    SetExits( ([
                "south" : "/domains/town/room/vill_road3",
                "northeast" : "/domains/town/room/voters",
                "up" : "/domains/town/room/mayor",
                "north" : "/domains/town/room/clerk.c",
                ]) );
    SetInventory(([]));

}
void init() {
    ::init();
    SetSmell(([]));
    SetListen(([]));
}
