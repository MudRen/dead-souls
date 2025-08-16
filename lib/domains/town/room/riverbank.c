#include <lib.h>
inherit LIB_FISHING;

protected void create() {
    ::create();
    SetTown("town");
    SetClimate("temperate");
    SetAmbientLight(30);
    SetShort("河岸");
    SetLong("这是一条狭窄但湍急的河流的河岸。一条陡峭的小路通向桥。河岸的陡峭东墙上有一个洞穴。");
    SetProperties (([
                "no attack":0, 
                "no bump":0, 
                "no steal":0, 
                "no magic":0, 
                "no paralyze":0, 
                "no teleport":0]));
    SetListen(([
                ({ "river", "water" }) : "你听到它奔流而过。",
                "default" : "你能听到河流奔涌的轰鸣声。",
                ]));
    SetInventory(([
                "/domains/town/npc/troll" : 1,
                "/domains/town/obj/rocks" : 1,
                "/domains/town/obj/riverwater" : 1,
                ]));
    AddExit("up", "/domains/town/room/bridge");
    if(unguarded( (: file_exists("/domains/cave/room/cave.c") :) ) ){
        AddExit("east", "/domains/cave/room/cave");
    }
    SetChance(90);
    SetFish( ([
                "/domains/town/meals/shark" : 10,
                ]) );
}
void init() {
    ::init();
    SetSmell(([]));
}

int CanReceive(object ob){
    if(answers_to("provost",ob)) return 0;
    return ::CanReceive();
}
