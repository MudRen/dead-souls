#include <medium.h>
#include <daemons.h>
#include <terrain_types.h>
#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int ActionFunction(){
    object *bodies = get_livings(this_object());
    if(!sizeof(bodies)) return 0;
    foreach(object body in bodies){
        int maxheal, maxstam, maxmag;
        int health, stamina, magic, poison;
        if((RACES_D->GetNonMeatRace(body->GetRace()))) continue;
        maxheal = (body->GetMaxHealthPoints()) * 0.85;
        maxstam = (body->GetMaxStaminaPoints()) * 0.85;
        maxmag = (body->GetMaxMagicPoints()) * 0.85;
        health =  (body->GetHealthPoints());
        stamina = (body->GetStaminaPoints());
        magic = (body->GetMagicPoints());

        if(health < maxheal){
            body->AddHP(random(10));
        }
        if(stamina < maxstam){
            body->AddStaminaPoints(random(15));
        }
        if(magic < maxmag){
            body->AddMagicPoints(random(15));
        }
        if(poison > 0 ){
            body->AddPoison(-(random(15)));
        }
    }
    return 1;
}

void create() {
    room::create();
    SetAmbientLight(30);
    SetDayLight(30);
    SetNightLight(30);
    SetShort("泉水底部");
    SetLong("这是天然泉水的基岩底部。一条通道向上延伸。\n%^BLUE%^这里有一个大的发光蛋。%^RESET%^");
    SetClimate("temperate");
    SetTown("wilderness");
    SetTerrainType(T_SEAFLOOR);
    SetMedium(MEDIUM_WATER);
    SetItems( ([
                ({ "shaft","passage" }) : "一条水下的垂直通道。"
                ({ "egg","large egg","large glowing egg","glowing egg" }) : "直径约一米，这个巨大的蛋似乎发光并随着能量脉动。"
                ]) );
    SetExits(([
                "up" : "/domains/town/room/forest_well1",
                ]));

    SetInventory(([
                "/domains/town/obj/hspringwater" : 1,
                "/domains/town/npc/giant_isopod" : 1,
                ]));
    set_heart_beat(6);
}
void init(){
    ::init();
}

void heart_beat(){
    ActionFunction();
}
