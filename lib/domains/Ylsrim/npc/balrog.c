/*    /domains/Ylsrim/npc/balrog.c
 *    From the Dead Souls Mud Library
 *    An example simple NPC
 *    Created by Descartes of Borg 960302
 */

#include <lib.h>

inherit LIB_NPC;

protected void create() {
    npc::create();
    SetKeyName("balrog");
    SetId("balrog");
    SetAdjectives("wicked", "ugly");
    SetShort("邪恶的炎魔");
    SetLong("炎魔是一种丑陋的生物，藏身于山脉中众多的裂缝和峡谷中。"
            "这只炎魔极其高大，显然对见到你并不太高兴。");
    SetLevel(8);         // level, race, and class determine NPC's power
    SetRace("balrog");   // must be some valid race from mraces command
    SetClass("fighter"); // needs a class!
    SetGender("male");
    SetEncounter(80);
    SetMorality(-800);   // -2000 absolute evil, 2000 absolute good
    SetAction(5, ({ "!growl" })); // Make him growl every now and then
}
