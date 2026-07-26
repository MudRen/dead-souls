#include <lib.h>
#include <position.h>

inherit LIB_VEHICLE;

protected void create() {
    vehicle::create();
    SetKeyName("hoverpod");
    SetId(({"pod", "vehicle","transport"}));
    SetAdjectives(({"small","shiny","cramped","metallic","hovering"}));
    SetShort("一个小型悬浮舱");
    SetLong("这是一个 shiny metallic sphere about 1.5 meters across， designed for containing an occupant and their stuff in its cramped interior and providing transportation。");
    SetVehicleInterior("这是一个 shiny sphere 的 cramped interior，用于 transportation。由于它悬浮，你可以使用 \"fly\" 命令来移动，例如：fly north");
    SetRace("vehicle");
    SetStat("strength", 50);
    SetPosition(POSITION_FLYING);
    SetMelee(0);
    SetNoClean(1);
    SetMount(1);
    SetMountStyle("driven");
    SetVisibleRiders(0);
    SetOpacity(0);
    SetMaxHealthPoints(20);
}
void init(){
    ::init();
}
