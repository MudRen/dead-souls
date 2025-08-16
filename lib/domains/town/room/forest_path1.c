#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetNightLight(10);
    SetDayLight(30);
    SetShort("森林小径");
    SetLong("你在镇外的森林里。向西南方向，小径继续通往一片空地。向东，它通往一座横跨河流的桥，通向镇上。各种树木和灌木丛包围着小径，使得向南走不可能，但向北植被变得稀疏。");
    SetItems( ([
                "forest" : "你在一条黑暗、令人毛骨悚然的森林小径上。植被茂密，不知何故给人一种压抑的感觉。",
                ({"plants","bushes","vegetation","tree","trees","bush"}) : 
                "植物、灌木和树木在这里生长得茂密而野性，限制了小径之外的视野。"
                "bridge" : "一座老桥在东边。"
                "clearing" : "看起来西边森林里有一片空地。"
                "path" : "你在森林小径上。"
                ]) );
    SetSkyDomain("town");
    SetExits( ([
                "north" : "/domains/town/virtual/forest/-4,1",
                "east" : "/domains/town/room/bridge",
                "southwest" : "/domains/town/room/clearing.c",
                ]) );
}
void init(){
    ::init();
}

int CanReceive(object ob){
    object env = environment(ob);
    if(!env || base_name(env) != "/domains/town/virtual/forest/24,1"){
        return ::CanReceive();
    }
    if(living(ob) && !interactive(ob) &&
            (!ob->GetRiders() || !sizeof(ob->GetRiders()))){
        ob->eventPrint("你发现自己无法离开森林。");
        return 0;
    }
    return ::CanReceive();
}
