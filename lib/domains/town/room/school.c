#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("乡村校舍");
    SetLong("这个简单的一室校舍不是特别宽敞，但它干净、维护良好，显然是乡村生活的重要组成部分。人们来这里学习，主要是语言，由流动的教师和客座讲师教授。");
    SetProperties (([
                "no attack":1, 
                "no bump":1, 
                "no steal":0, 
                "no magic":0, 
                "no paralyze":0, 
                "no teleport":0]));
    SetItems(([]));
    SetInventory(([
                "/domains/town/npc/bugg" : ({60, 1}),
                ]));
    SetExits(([
                "south" : "/domains/town/room/vill_road4",
                ]));

}
void init() {
    ::init();
    SetSmell(([]));
    SetListen(([]));
}
