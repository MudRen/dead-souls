#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("no castle", 1);
    SetShort( "兽人谷入口");
    SetLong(
            "在西面达罗克山脉的阴影下，大公路的正北方就是兽人谷。"
            "在这里你可以看到一座巨大的石头兽人堡垒的入口，"
            "四周被茂密的森林环绕。大公路在你南面。");
    SetItems(
            (["mountains" : "西北方一片黑暗的山脉。西南方的山脉"
             "被称为命运山脉。",
             "highway" : "你无法透过树木看到它。",
             "valley" : "它坐落在达罗克山脉的阴影中。",
             "entrance" : "一座宏伟的石头大门通向兽人堡垒。",
             "stone" : "一块古老的灰色石头，已在此矗立了无数岁月。",
             "fortress" : "这里是居住在兽人谷的兽人们的家园。",
             "forest" : "这里的树木极其茂密。",
             "trees" : "它们高大而密集地生长在一起。",
             "gateway" : "兽人堡垒的入口。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["north" : "/domains/Praxis/orc_valley/open",
             "south" : "/domains/Praxis/highway3"]) );
    AddExit("north", "/domains/Praxis/orc_valley/open", (: "go_north" :) );
}

void reset() {
    int i, x;
    object ob, thing;

    ::reset();
    if(!present("orc")) {
        for(i=0; i< 3; i++) {
            ob = new(LIB_NPC);
            ob->SetKeyName("guard");
            ob->SetId( ({ "orc", "orc guard", "guard" }) );
            ob->SetShort( "兽人守卫");
            ob->SetLong( "他对你这样的人出现在附近感到很不高兴。");
            ob->SetRace( "orc");
            ob->SetGender("male");
            ob->SetLevel(4);
            ob->SetHealthPoints(77);
            ob->SetMorality(-75);
            ob->SetAggressive( 15);
            ob->SetWielding_limbs( ({ "right hand", "left hand" }) );
            ob->move(this_object());

            thing = new(LIB_ITEM);
            thing->SetKeyName("axe");
            thing->SetId( ({ "axe", "hand axe" }) );
            thing->SetShort( "手斧");
            thing->SetLong( "这显然是兽人制造的。");
            thing->SetType("knife");
            thing->SetClass(8);
            thing->SetMass(223);
            thing->SetValue(90);
            thing->move(ob);
            ob->eventForce("wield axe in right hand");
        }
    }
}

int go_north() {
    if(present("orc")) {
        present("orc")->eventForce("speak in orcish 没人能从我们这里过去！");
        return 0;
    }
    else return 1;
}

void init(){
    ::init();
}
