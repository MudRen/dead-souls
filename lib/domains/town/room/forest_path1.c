#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetNightLight(10);
    SetDayLight(30);
    SetShort("森林小径");
    SetLong("你在城镇外的一片森林中。西南方向的小径通向一片空地，东边通向一座跨越河流、通往城镇的桥。各种树木和灌木丛生在小径两旁，使得无法向南前进，但北边的植被较为稀疏。");
    SetItems( ([
                "forest" : "你在一条黑暗、令人毛骨悚然的森林小径上。植被茂密，给人一种压抑的感觉。",
                ({"plants","bushes","vegetation","tree","trees","bush"}) :
                "植物、灌木和树木在这里生长得茂密而野性，限制了小径以外的视野。",
                "bridge" : "东边有一座古老的桥。",
                "clearing" : "西边的森林里似乎有一片空地。",
                "path" : "你在森林中的一条小径上。"
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
        ob->eventPrint("You find yourself unable to leave the forest.");
        return 0;
    }
    return ::CanReceive();
}
