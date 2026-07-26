#include <lib.h>
inherit "/lib/npc";

#include <daemons.h>

void create() {
    ::create();
    SetKeyName("armageddon");
    SetId( ({ "armageddon", "crasher", "asshole", "game crasher", "armageddon the game crasher" }) );
    SetShort("游戏崩溃者末日博格");
    SetLong("他只短暂出现一次，只为给泥潭带来毁灭。\n");
    SetLevel(33);
    SetHealthPoints(10000);
    SetRace("human");
}

