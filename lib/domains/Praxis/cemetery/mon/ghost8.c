inherit "/lib/npc";

void create() {
    ::create();
    SetKeyName("shadowwolf's ghost");
    SetId( ({ "ghost","shadowwolf","Shadowwolf","Shadowwolf's Ghost" }) );
    SetShort( "影狼的幽灵");
    SetAggressive( 0);
    SetLevel(1);
    SetLong( "幽灵是一个苍白的幽灵，紧紧地将一个NI抱在胸前。");
    SetMorality(100);
    SetRace( "wraith");
    SetGender("male");
    SetMaxHealthPoints(25);
    SetHealthPoints(5);
    SetRace("human");
    RemoveLimb("left foot",this_object());
    RemoveLimb("right hand",this_object());
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
    if(sscanf(str, "%stickle%s", a, b) == 2) tell_room(environment(this_object()), "幽灵说：这只是皮肉伤！！", ({this_object()}));
}
