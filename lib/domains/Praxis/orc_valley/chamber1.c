#include <lib.h>
inherit "/lib/std/room";

void create() {
    ::create();
    SetProperty("light", 0);
    SetProperty("indoors", 1);
    SetShort( "兽人士兵的房间");
    SetLong(
            "你身处兽人堡垒内一间黑暗的生活房间中。"
            "西面的通道通向庭院。");
    SetItems(
            (["chamber" : "房间很小，几乎没有家具。",
             "furnishings" : "没什么值得注意的东西。",
             "passage" : "它通向庭院。"]) );
    SetExits( (["west" : "/domains/Praxis/orc_valley/passage1"]) );
}

void reset() {
    object ob, thing;

    ::reset();
    if(!present("orc")) {
        ob = new("/lib/npc");
        ob->SetKeyName("soldier");
        ob->SetId( ({ "orc", "orc soldier", "soldier" }) );
        ob->SetShort( "兽人士兵");
        ob->SetLong( "他长得很丑，对你的到来感到非常不快。");
        ob->SetClass("fighter");
        ob->SetSkill("blunt", 50);
        ob->SetRace( "orc");
        ob->SetGender("male");
        ob->SetLevel(7);
        ob->SetHealthPoints(129);
        ob->SetMorality(-135);
        ob->SetAggressive( 18);
        ob->SetRace("human");
        ob->SetWielding_limbs( ({ "right hand", "left hand" }) );
        ob->move(this_object());

        thing = new(LIB_ITEM);
        thing->SetKeyName("mace");
        thing->SetId( ({ "mace", "battle mace" }) );
        thing->SetShort( "战斗锤");
        thing->SetLong( "这显然是兽人制造的。");
        thing->SetType("blunt");
        thing->SetClass(14);
        thing->SetAC(3);
        thing->SetMass(312);
        thing->SetValue(171);
        thing->move(ob);
        ob->eventForce("wield mace in right hand");
    }
}
void init(){
    ::init();
}

