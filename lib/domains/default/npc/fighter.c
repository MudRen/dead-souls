#include <lib.h>
inherit LIB_NPC;

protected void create(){
    npc::create();
    SetKeyName("fighter");
    SetId( ({"human","npc","warrior","fighter"}) );
    SetShort("一名战士");
    SetLong("这是一个魁梧的人类战士。即使隔着盔甲，他的胸肌也清晰可见。他的脸上布满了大胆的蓝色纹身。");
    SetClass("fighter");
    SetLevel(10);
    SetCustomXP(350);
    SetRace("human");
    SetStat("strength", 30);
    SetGender("male");
    SetInventory(([
                "/domains/default/armor/chainmail.c" : "wear chainmail",
                "/domains/default/weap/sharpsword.c" : "wield sword"
                ]));
    SetCurrency( ([
                "silver" : 100,
                ]) );
    SetHealthPoints(549);
    SetMaxHealthPoints(550);
}
void init(){
    ::init();
}
