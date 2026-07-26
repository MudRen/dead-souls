inherit "/lib/npc";

void create() {
    ::create();
    SetKeyName("atmos");
    SetId( ({ "atmos" }) );
    SetShort("高级凡人阿特摩斯，普拉克西斯之主");
    SetAggressive( 0);
    SetLevel(26);
    SetLong("阿特摩斯是普拉克西斯和所有高级凡人的主人。\n");
    SetMorality(1000);
    SetRace( "human");
    SetMaxHealthPoints(800000);
    SetHealthPoints(400000);
    SetRace("human");
}
