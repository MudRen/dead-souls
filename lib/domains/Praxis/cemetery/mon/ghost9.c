inherit "/lib/npc";

void create() {
    ::create();
    SetKeyName("test ghost");
    SetId( ({ "test ghost" }) );
    SetLevel(1);
    SetShort( "测试幽灵");
    SetLong( "是的，这是一个幽灵。");
    SetRace( "wraith");
    SetGender("neuter");
    SetAggressive( 0);
    SetMorality(200);
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
    if(sscanf(str, "%ssmiles%s", a, b) == 2) tell_room(environment(this_object()), "小幽灵哀怨地问道：为什么神灵不喜欢我？", ({this_object()}));
}
