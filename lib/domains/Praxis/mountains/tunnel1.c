#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 0);
    SetProperty("indoors", 1);
    SetProperty("no teleport", 1);
    SetShort( "山下的黑暗隧道");
    SetLong(
            "这条下行隧道中有微弱的光线，但不足以照亮这条通道。"
            "洞穴从主隧道的东西两侧分支出去。");
    SetItems(
            (["light" : "什么光？",
             "tunnel" : "非常黑暗。",
             "chamber" : "你看不太清楚。",
             "chambers" : "东边有一个，西边有一个，但你看不清里面的任何东西。"]) );
    SetExits( 
            (["east" : "/domains/Praxis/mountains/chamber1",
             "west" : "/domains/Praxis/mountains/chamber2",
             "down" : "/domains/Praxis/mountains/tunnel2",
             "up" : "/domains/Praxis/mountains/entrance"]) );
}

void reset() {
    object arm, mon;

    ::reset();
    if(!present("goblin")) {
        mon = new(LIB_NPC);
        mon->SetKeyName("goblin");
        mon->SetId( ({ "guard", "goblin", "goblin guard" }) );
        mon->SetLevel(4);
        mon->SetShort( "哥布林守卫");
        mon->SetLong( "一个丑陋的怪物，可能从未见过天日。");
        mon->SetRace( "goblin");
        mon->set_stats("strength", 5);
        mon->SetAggressive( 10);
        mon->set_languages( ({ "goeblesque" }) );
        mon->set_speech(10, "goeblesque",
                ({ "Get the hell out of here, asshole!", "You will never get that "
                 "damn crystal ball!", "I will freaking kill you!"}), 0);
        mon->set_speech(20, "goeblesque", ({ "You are dead!", 
                    "Shouldn't have picked a fight with me!", "I will body slam you!",
                    "%&$*!head!" }), 1);
        mon->SetMorality(-120);
        mon->SetHealthPoints(400);
        mon->SetGender("male");
        mon->SetRace("human");
        mon->move(this_object());

        arm = new(LIB_ARMOR);
        arm->SetKeyName("chainmail");
        arm->SetId( ({ "chainmail", "suit of chainmail", "suit" }) );
        arm->SetShort( "一套锁子甲");
        arm->SetLong( "一套生锈的旧锁子甲。");
        arm->set_type("body armour");
        arm->set_limbs( ({ "torso", "left arm", "left leg", "right arm", "right leg" }) );
        arm->set_ac(5);
        arm->set_mass(900);
        arm->set_value(100);
        arm->move(mon);
        mon->force_me("wear suit");
    }
}

int CanReceive() {
    if(previous_object()->query_level() > 10) {
        message("my_action", "一股魔力阻止你进入山的更深处。", this_player());
        return 0;
    }
    return 1;
}
