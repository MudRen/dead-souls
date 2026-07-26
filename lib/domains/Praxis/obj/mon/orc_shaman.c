inherit "/lib/npc";

create() {
    ::create();
    SetKeyName("shaman");
    SetId( ({ "shaman", "orc", "orc shaman" }) );
    SetShort("高阶兽人萨满");
    SetAggressive( 29);
    SetLevel(13);
    SetLong("她是一位强大的黑暗法师，也是兽人山谷兽人的领袖。\n");
    SetMorality(-515);
    SetGender("female");
    SetClass("mage");
    SetRace( "orc");
    SetHealthPoints(220);
    SetMagicPoints(350);
    SetRace("human");
    SetSkill("magic attack", 60);
    SetProperty("no bump", 1);
}
