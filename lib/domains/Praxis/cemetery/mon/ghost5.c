inherit "/lib/npc";

void create() {
    ::create();
    SetKeyName("forlock's ghost");
    SetId( ({ "ghost","forlock","Forlock","Forlock's Ghost" }) );
    SetShort( "福洛克的幽灵");
    SetAggressive( 0);
    SetLevel(1);
    SetLong( "这是福洛克悲伤的幽灵，迷失了，失去了凡人伙伴。");
    SetMorality(200);
    SetRace( "wraith");
    SetGender("male");
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
    if(sscanf(str, "%ssmiles%s", a, b) == 2) tell_room(environment(this_object()), "福洛克的幽灵苦笑着，问你有没有看到他的泥潭。", ({this_object()}));
}
