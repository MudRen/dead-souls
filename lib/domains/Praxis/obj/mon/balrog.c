inherit "/lib/npc";

create() {
    ::create();
    SetKeyName("balrog");
    SetId( ({ "balrog" }) );
    SetShort("一只邪恶的炎魔");
    SetAggressive( 17);
    SetLevel(9);
    SetLong("他是达洛克山脉的守护者之一。\n");
    SetRace("human");
    SetMorality(-200);
    SetRace( "balrog");
    SetHealthPoints(360);
    SetMagicPoints(200);
}
