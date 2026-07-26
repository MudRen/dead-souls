inherit "/lib/npc";

void create() {
    ::create();
    SetKeyName("flamme's ghost");
    SetId( ({ "ghost","flamme","Flamme","Flamme's Ghost" }) );
    SetShort( "弗拉梅的幽灵");
    SetAggressive( 0);
    SetLevel(1);
    SetLong( "幽灵仍然有几缕红褐色的头发向各个方向翘起。"
            "她在微笑，但脸上带着相当惊讶的表情。");
    SetMorality(600);
    SetRace( "wraith");
    SetGender("female");
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
    if(sscanf(str, "%ssmiles%s", a, b) == 2) tell_room(environment(this_object()), "小幽灵问道：我怎么了？", ({this_object()}));
}
