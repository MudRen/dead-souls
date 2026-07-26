inherit "/lib/npc";

void create() {
    ::create();
    SetKeyName("Melissa's Ghost");
    SetId( ({ "ghost","melissa","Melissa","Melissa's Ghost" }) );
    SetShort( "梅丽莎的幽灵");
    SetAggressive( 0);
    SetLevel(1);
    SetLong( "一个穿着飘逸白色长裙的朦胧身影。"
            "她正扭着双手哭泣。");
    SetMorality(200);
    SetRace( "wraith");
    SetGender("female");
    SetCurrency("gold",random(50));
    SetMaxHealthPoints(25);
    SetHealthPoints(25);
    SetRace("human");
}

void catch_tell(string str) {
    object ob;
    string a, b, c;

    if(sscanf(str, "%s gives %s to you", a, b) == 2) {
        ob = present( lower_case(a), environment(this_object()));
        if(ob) {
            tell_object(ob, "幽灵感谢你的慷慨。");
            tell_room(environment(this_object()), "幽灵感谢"+a+"的慷慨。", ({this_object(), ob}));
        }
    }
    if(sscanf(str, "%ssmiles%s", a, b) == 2)
        tell_room(environment(this_object()), "小幽灵可怜地哭泣着。", ({this_object()}));
}
