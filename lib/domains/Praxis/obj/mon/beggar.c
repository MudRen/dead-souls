#include <lib.h>

inherit LIB_SENTIENT;


int left_hand;
void complete_quest(object ob);

create() {
    ::create();
    SetKeyName("beggar");
    SetId( ({ "beggar" }) );
    SetShort("一个可怜的乞丐");
    SetAggressive( 0);
    SetWanderSpeed(60);
    SetGender("male");
    SetLevel(4);
    SetLong("他只是一个想要几枚硬币的可怜乞丐。\n");
    SetEncounter(0);
    SetMorality(30);
    SetRace( "human");
    SetMaxHealthPoints(50);
    SetHealthPoints(50);
    AddLimb("head", "FATAL", 25, 0, 4);
    AddLimb("torso", "FATAL", 50, 0, 4);
    AddLimb("right arm", "right hand", 20, 0, 4);
    AddLimb("right hand", "", 15, 0, 4);
    AddLimb("left arm", "left hand", 20, 0, 4);
    AddLimb("left hand", "", 15, 0, 4);
    AddLimb("right leg", "right foot", 25, 0, 4);
    AddLimb("right foot", "", 20, 0, 4);
    AddLimb("left leg", "left foot", 25, 0, 4);
    AddLimb("left foot", "", 20, 0, 4);
    RemoveLimb("left hand",this_object());
    left_hand = 0;
    new("/domains/Praxis/obj/misc/cold")->infect(this_object());
}
void catch_tell(string str) {
    object ob;
    string a, b, c;

    if(sscanf(str, "%s quest%*s", a)) {
        call_out("say_line", 2, "乞丐说：什么任务？我什么任务都不知道。\n");
        return;
    }
    if(sscanf(str, "%s regenerates your %s", a, b) == 2) {
        if(left_hand) return;
        if(!(ob=present((a=lower_case(a)), environment(this_object())))) return;
        //if(!query_is_limb("left hand")) return;
        left_hand = 1;
        call_out("complete_quest", 1, ob);
        return;
    }
    if(sscanf(str, "%s says: %s hand%*s", a, b) == 2) {
        //if(query_is_limb("left hand"))
        //call_out("say_line", 2, "The beggar says: My left hand is doing fine now!\n");
        //        else
        call_out("say_line", 2, "乞丐说：我希望它能被替换掉。\n");
        return;
    }
    if(sscanf(str, "%s gives %s you", a, b) == 2) {
        ob = present( lower_case(a), environment(this_object()));
        if(ob) {
            tell_object(ob, "乞丐感谢你的慷慨。\n");
            tell_room(environment(this_object()), "乞丐感谢"+a+"的慷慨。\n", ({this_object(), ob}));
        }
    }
    if(sscanf(str, "%s?", a)) {
        call_out("say_line", 2, "乞丐说：我不明白这个问题。\n");
        return;
    }
    if(sscanf(str, "%ssmiles%s", a, b) == 2)
        call_out("say_line", 2, "乞丐开心地笑了。\n");
    AddAlcohol(200);
}
void complete_quest(object ob) {
    if(!ob->set_mini_quest("beggar", 5000,
                "你替一个可怜的乞丐换上了缺失的左手。\n")) {
        tell_object(ob, "乞丐感谢你。\n");
        tell_room(environment(this_object()), "乞丐感谢"+ob->query_cap_name()+"。\n", ({ ob, this_object() }) );
        SetAction(5, ob->query_cap_name()+"替我换上了缺失的左手！");
        return;
    }
    tell_object(ob, "乞丐满意地笑了！\n");
    tell_object(ob, "乞丐说：太感谢你了！\n");
    tell_object(ob, "你感觉更有经验了。\n");
    tell_room(environment(this_object()), ob->query_cap_name()+"看起来更有经验了。\n", ({ ob, this_object() }) );
    SetAction(5, ob->query_cap_name()+"替我换上了缺失的左手！" );
}
void say_line(string str) {
    tell_room(environment(this_object()), str, ({ this_object() }) );
}
void init(){
    ::init();
}
