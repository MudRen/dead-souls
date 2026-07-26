inherit "/lib/npc";

create() {
    ::create();
    SetKeyName("goblin");
    SetId( ({ "goblin", "soldier" }));
    SetShort( "一个哥布林士兵");
    SetAggressive( 17);
    SetLevel(5);
    SetLong( "达洛克哥布林的战士。");
    SetClass("fighter");
    SetRace("human");
    SetMorality(-200);
    SetRace( "goblin");
    SetHealthPoints(300);
    SetMagicPoints(200);
}
