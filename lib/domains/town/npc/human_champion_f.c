#include <lib.h>
inherit LIB_NPC;
protected void create(){
    npc::create();
    SetKeyName("human champion");
    SetId( ({ "champion", "human","npc","warrior"}) );
    SetShort("一位人类勇士");
    SetLong("这是一位魁梧的人类战士。即使透过她的盔甲，她巨大的肌肉也清晰可见。她的脸上带着愤怒和仇恨的咆哮表情。");
    SetLevel(10);
    SetRace("human");
    SetClass("fighter");
    SetGender("female");
    SetInventory(([
                "/domains/campus/armor/chainmail.c" : "wear chainmail",
                //"/domains/campus/armor/shield.c" : "wear shield",
                "/domains/campus/weap/sharpsword.c" : "wield sword"
                ]));
    //SetMaxHealthPoints(550);
}
