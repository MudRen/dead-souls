inherit "/lib/npc";

void create() {
    ::create();
    SetKeyName("darkone's ghost");
    SetId( ({ "ghost","darkone","Darkone","Darkone's Ghost" }) );
    SetShort( "暗影，歪脖子的幽灵");
    SetAggressive( 0);
    SetLevel(1);
    SetLong( "这是暗影的邪恶幽灵。他笑得如此邪恶，"
            "以至于头上长出了巨大的黑角。"
            "他非常悲伤，因为他再也不能通过在城堡里挑刺来折磨巫师了。");
    SetMorality(-600);
    SetRace( "wraith");
    SetGender("neuter");
    SetMaxHealthPoints(25);
    SetCurrency("gold",25);
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
        tell_room(environment(this_object()), "暗影的幽灵"
                "大声呻吟：嗷呜呜呜呜...*咯*（嚎叫声突然中断了。）", ({this_object()}));
}
