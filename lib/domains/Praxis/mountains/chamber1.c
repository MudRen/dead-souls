#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", -1);
    SetProperty("indoors", 1);
    SetProperty("no teleport", 1);
    SetProperty("no castle", 1);
    SetShort( "黑暗的地下洞穴");
    SetLong(
            "你在一个非常黑暗的洞穴中，只有你的光源才能照亮。"
            "这里的恶臭令人作呕，而且挥之不去。");
    SetItems(
            (["light" : "什么光？",
             "tunnel" : "非常黑暗。",
             "chamber" : "你看不太清楚。"]) );
    SetExits( 
            (["west" : "/domains/Praxis/mountains/tunnel1"]) );
}

void reset() {
    object arm, mon;

    ::reset();
    if(!present("goblin")) {
        mon = new(LIB_NPC);
        mon->SetKeyName("goblin");
        mon->SetId( ({ "soldier", "goblin", "goblin soldier" }) );
        mon->SetLevel(3);
        mon->SetShort( "哥布林士兵");
        mon->SetLong( "一个丑陋的怪物，可能从未见过天日。");
        mon->SetRace( "goblin");
        mon->SetAggressive( 10);
        mon->SetMorality(-140);
        mon->SetHealthPoints(240);
        mon->set_languages( ({ "goeblesque" }) );
        mon->set_speech(10, "goeblesque", ({ "Piss off!", "Die, asshole!" }),
                1);
        mon->SetGender("female");
        mon->SetRace("human");
        mon->move(this_object());
        arm = new(LIB_ARMOR);
        arm->SetKeyName("boot");
        arm->SetId( ({ "boot", "boot", "goblin boot" }) );
        arm->SetShort( "右脚哥布林靴子");
        arm->SetLong( "一只右脚靴子，由哥布林能找到的腐烂皮革制成。");
        arm->set_type("boot");
        arm->set_limbs( ({ "right foot" }) );
        arm->set_ac(3);
        arm->set_mass(120);
        arm->set_value(50);
        arm->move(mon);
        mon->force_me("wear boot");
    }
}

