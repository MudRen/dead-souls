#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetTown("town");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("村学堂");
    SetLong("这座简朴的单间学堂虽然不大，但干净整洁、维护良好，显然是村庄生活的重要组成部分。人们来这里接受巡回教师和客座讲师的教导，主要是学习语言。");
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
