#include <lib.h>

inherit LIB_NPC;

protected void create() {
    npc::create();
    SetKeyName("thief");
    SetId(({"thief in a bathtowel","thief in a towel","thief"}));
    SetAdjectives(({"wet"}));
    SetShort("一个裹着浴巾的贼");
    SetLong("从他鬼祟的外表和举止来看，这显然是一个潜入豪宅并定居下来的贼。你似乎在他刚洗完澡时就撞见了他。");
    SetLevel(1);
    SetRace("human");
    SetClass("thief");
    SetGender("male");
    SetEncounter(100);
    SetMaxHealthPoints(25);
    SetInventory(([
                "/domains/town/armor/towel":"wear towel",
                "/domains/town/weap/brush":"wield brush",
                ]) );
    SetHealthPoints(50);
    SetGuard("down", "湿漉漉的贼挡住了你的去路！" );
}
void init(){
    ::init();
}
