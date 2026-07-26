inherit "/lib/sentient";

int count_eggs;

void create() {
    ::create();
    SetKeyName("easter bunny");
    SetId(  ({ "bunny", "easter bunny" }) );
    SetShort( "复活节兔子");
    SetLong( "蹦蹦跳跳。\n哦，快乐啊，是复活节兔子。\n看着它流口水。\n它正在噩梦世界各处藏复活节彩蛋。\n");
    SetAggressive( 0);
    SetWanderSpeed(30);
    SetGender("male");
    SetLevel(30);
    SetMorality(200);
    SetRace("rodent");
    SetMaxHealthPoints(500000);
    SetHealthPoints(500000);
    SetAction(10,
            ({ "复活节兔子流口水。\n",
             "复活节兔子对你放了个屁。\n",
             "复活节兔子困惑地四处张望。\n",
             "复活节兔子咕哝着关于臭鸡蛋的事。\n" })
            );
    SetSkill("melee", 400);
    SetRace("rodent");
}

void catch_tell(string str) {
    string who;

    //if(!interact("enters", str)) return;
    sscanf(str, "%s enters%*s", who);
    who = lower_case(who);
    call_out("egghead", 2, who);
}

void egghead(string who) {
    object ob, it;

    ob = present(who, environment(this_object()));
    if(!ob) return;
    if(random(101) < 25) {
        tell_object(ob, "复活节兔子朝你扔了一个蛋！\n");
        tell_room(environment(this_object()), "复活节兔子朝"+ob->query_cap_name()+"扔了一个蛋。\n", ({ ob }));
        it = new("/domains/Praxis/obj/misc/easter_egg");
        it->move(ob);
    }
}

void heart_beat() {
    object it;
    count_eggs++;
    if(count_eggs > 60) {
        count_eggs = 0;
        it = new("/domains/Praxis/obj/misc/easter_egg");
        it->move(this_object());
        eventForce("hide egg");
    }
    ::heart_beat();
}
