inherit "/lib/npc";

create() {
    ::create();
    SetKeyName("knight");
    SetId( ({ "knight" }) );
    SetShort("一位当地骑士");
    SetLevel(13);
    SetLong( "她伸张正义。\n");
    SetGender("female");
    SetRace( "human");
    SetMorality(300);
    SetHealthPoints(450);
    AddLimb("head", "FATAL", 100, 0, 4);
    AddLimb("torso", "FATAL", 201, 0, 4);
    AddLimb("right arm", "right hand", 70, 0, 4);
    AddLimb("right hand", "", 50, 0, 4);
    AddLimb("left arm", "left hand", 70, 0, 4);
    AddLimb("left hand", "", 50, 0, 4);
    AddLimb("right leg", "right foot", 70, 0, 4);
    AddLimb("right foot", "", 50, 0, 4);
    AddLimb("left leg", "left foot", 70, 0, 4);
    AddLimb("left foot", "", 50, 0, 4);
}

void catch_tell(string str) {
    object tp;
    string a, b, c;

    if(sscanf(str, "%suest%s", a, b) == 2) {
        tell_room(environment(this_object()), "骑士说：我为了追求荣耀而冒险进入了哥布林洞穴。\n我差点丢了性命才逃出来。\n虽然我现在很受尊敬，但我仍然因为丢失了\n曾祖父的魔法水晶球而感到无颜面。\n请把它还给我！\n", ({ this_object() }));
        return;
    }
    if(sscanf(str, "%s gives you %s", a, b) == 2) {
        a = lower_case(a);
        tp = present(a, environment(this_object()));
        if(!tp) return;
        call_out("check_ball", 2, tp);
        return;
    }
}

void check_ball(object tp) {
    object ob;

    ob = present("honor_quest_ob", this_object());
    if(!ob) {
        tell_object(tp, "这很好，但不是我要找的东西。\n");
        return;
    }
    ob->destruct();
    if(!tp->set_quest("honor")) return;
    tell_object(tp, "骑士说：你恢复了我的荣誉！\n骑士非常感谢你。\n");
    tell_object(tp, "骑士支付给你10000铜币作为奖励。\n");
    tp->AddCurrency("copper", 10000);
    tp->add_exp(500);
    tp->add_alignment(20);
}
