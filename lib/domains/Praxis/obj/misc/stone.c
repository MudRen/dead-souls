//  /domains/Praxis/obj/misc/stone.c
//  Stone for throwing at criminals and stuff.
//  For the Nightmare mortal law system
//  Created by Manny@Nightmare 940901

#include <lib.h>

inherit LIB_ITEM;

object target;
void set_target(object who);

create() {
    ::create();
    SetKeyName("stone");
    SetId( ({ "stone", "throwing stone" }) );
    SetShort("一块投掷石");
    SetLong( (: "long_func" :) );
    SetMass(2);
    SetValue(0);
}

void long_func() {
    if(target) {
        message("say", "一块等待着被扔向"+
                target->query_cap_name()+"额头的投掷石。", this_player());
    } else {
        message("say", "一块没有目标的投掷石。",
                this_player());
    }
}

void init() {
    ::init();
    add_action("throw_stone", "throw");
}

int throw_stone(string str) {
    string what, who;
    string limb;

    if(!str) {
        notify_fail("扔什么？\n");
        return 0;
    }
    if(!sscanf(str, "%s at %s", what, who) == 2) {
        notify_fail("扔什么打谁？\n");
        return 0;
    }
    if(!id(what)) {
        notify_fail("扔什么？\n");
        return 0;
    }
    if(who != target->query_name()) {
        message("say", "石头完全没打中。", this_player());
        message("say", this_player()->query_cap_name()+"朝某个随机方向扔了一块石头。", environment(this_player()),
                this_player());
        return 1;
    }
    switch(random(4)) {
        case 0:
            message("say", "你正中"+target->query_cap_name()+"的额头！！", this_player());
            message("say", this_player()->query_cap_name()+"用石头击中了"+
                    target->query_cap_name()+"的额头。",
                    environment(this_player()), ({ this_player(), target }) );
            message("say", this_player()->query_cap_name()+"用一块小石头"
                    "正中你的头部！！", target);
            limb = "head";
            break;
        case 1:
            message("say", target->query_cap_name()+"痛苦地尖叫，"
                    "因为你正中了"+target->query_possessive()+"的鼻子！", this_player());
            message("say", target->query_cap_name()+"痛苦地尖叫，"
                    "因为"+this_player()->query_cap_name()+"正中了"
                    +target->query_possessive()+"的鼻子！", environment(this_player()),
                    ({ this_player(), target }) );
            message("say", "你痛苦地尖叫，因为一块石头砸进了你的鼻子！！", target);
            limb = "head";
            break;
        case 2:
            message("say", "哎哟！你的石头正中了"+
                    target->query_possessive()+"的要害！！", this_player());
            message("say", this_player()->query_cap_name()+"的石头扔得真准...",
                    environment(this_player()), ({ this_player(), target }));
            message("say", this_player()->query_cap_name()+"正中了你的要害！！哎哟！", target);
            limb = "torso";
            break;
        case 3:
            message("say", "你把一块石头正中了"+
                    target->query_possessive()+"的肚子。", this_player());
            message("say", this_player()->query_cap_name()+"无情地"
                    "用石头砸"+target->query_cap_name()+"。",
                    environment(this_player()), ({ this_player(), target }));
            message("say", this_player()->query_cap_name()+"把一块石头"
                    "砸进了你的肚子，让你喘不过气来。", target);
            limb = "torso";
            break;
    }
    target->do_damage(limb, random(50)+10);
    if((target->check_on_limb(limb) == 2) || (target->query_hp() < 0)) 
        target->die();
    return 1;
}

void set_target(object who) { target = who; }
