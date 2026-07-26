#include <lib.h>
#include <daemons.h>
#include ROOMS_H

inherit LIB_ROOM;

void create(){
    room::create();
    SetAmbientLight(30);
    SetShort("焚化炉");
    SetLong("焚化炉。到达这里的物品都会被焚化。你可能不应该待在这里。往下走可以离开。");
    SetProperties(([
                "no attack" : 1,
                ]));
    SetExits( ([ "down" : ROOM_START ]) );
    if(base_name(this_object()) != LIB_FURNACE){
        call_out((: reload_room :), 600, load_object(base_name(this_object())));
        set_heart_beat(1);
    }
    SetNoModify(1);
}

int CanReceive(object ob){
    return room::CanReceive(ob);
}

void init(){
    ::init();
}

void heart_beat(){
    if(base_name(this_object()) != LIB_FURNACE){
        if(sizeof(all_inventory(this_object()))){
            foreach(object ob in deep_inventory(this_object())){
                if(ob && interactive(ob)) 
                    ob->eventMove(ROOMS_D->GetVoid(ob));
                else ob->eventDestruct();
            }
        }
    }
}
