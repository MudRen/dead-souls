/*  /cmds/verbs/player/bump.c
 *  Allows players to possibly bump a target into another room
 *  created by Blitz@Dead Souls
 */

#include <lib.h>
#include <damage_types.h>
#include "include/bump.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("bump");
    SetRules("LIV");
    SetErrorMessage("你想撞开谁？");
    SetHelp( "Syntax: bump <LIVING>\n\n"        
            "This command allows you bump the living object named "
            "into an adjacent room.  It is quite possible that "
            "bumping may cause you bodily injury.");
}

mixed can_bump_liv() {
    object env = environment(this_player());
    if( !env ) return "你哪里也不在！";
    if( env->GetProperty("no bump") )
        return "神秘力量阻止了你的推挤行为。";
    return 1;
}

mixed do_bump_liv(object ob) {
    int Strength, TargetStrength;
    string *Exits;
    string NewLocation, OldLocation;
    mixed var;
    object env;

    if( !ob ) return 0;
    if( !(env = environment(ob)) ) return 0;
    if( ob->GetProperty("no bump") ) {
        message("my_action", "你试图撞开"+
                ob->GetCapName()+"。",
                this_player() );
        message("other_action", this_player()->GetCapName()+"试图"
                "撞开"+ob->GetCapName()+"。",
                environment(ob), ({ ob, this_player() }) );
        message("other_action", this_player()->GetCapName()+"试图"
                "撞开你。",
                ob);
        if( !playerp(ob) )
            ob->eventForce("growl "+this_player()->GetKeyName());
        return 1;
    }
    if( var = ob->eventBump(this_player()) ) return var;
    this_player()->AddStaminaPoints( -(random(15) + 3) );
    if( ( ob->GetStatLevel("agility") / 2 ) >
            ( this_player()->GetStatLevel("strength")) ) {
        message("my_action", "你灵巧地闪开了"+
                possessive_noun(this_player()->GetCapName())+"撞开你的企图。",
                ob);
        message("other_action", ob->GetCapName()+"灵巧地闪开了"
                "你试图撞开"+objective(ob)+"的企图。",
                this_player() );
        message("other_action", ob->GetCapName()+"灵巧地闪开了"+
                possessive_noun(this_player()->GetCapName())+"撞开"+objective(ob)+"的企图。",
                env, ({ this_player(), ob }));
        return 1;
    }
    Strength = this_player()->GetStatLevel("strength") +
        random(this_player()->GetStatLevel("speed") / 2);
    TargetStrength = ob->GetStatLevel("strength") +
        random( ob->GetStatLevel("agility") / 2 );
    if( (Strength - TargetStrength) < -10 ) {
        this_player()->eventReceiveDamage(ob, BLUNT, random(5) + 1);
        message("other_action", ob->GetCapName()+"把你"
                "推倒在地！",
                this_player() );
        message("my_action", this_player()->GetCapName()+"在试图撞开你时"
                "被推倒在地。",
                ob);
        message("other_action", this_player()->GetCapName()+"在试图撞开"
                +ob->GetCapName()+"时被推倒在地。",
                env, ({ ob, this_player() }) );
        return 1;
    }
    else if( (Strength - TargetStrength) < (5 + random(20)) ) {
        this_player()->eventReceiveDamage(ob, BLUNT, random(3) + 1);
        message("my_action", "你未能将"+ob->GetCapName()+"撞开。", this_player() );
        message("other_action", this_player()->GetCapName()+"试图撞开你"
                "但失败了。",
                ob);
        message("other_action", this_player()->GetCapName()+"试图撞开"
                +ob->GetCapName()+"但失败了。",
                environment(ob), ({ ob, this_player() }) );
        return 1;
    } else {
        this_player()->AddStatPoints("strength", random(5));
        Exits = env->GetExits();
        Exits = filter(Exits,
                (: !(object)$(env)->GetDoor($1) ||
                 !(object)$(env)->GetDoor($1)->GetClosed() :) );
        if( !sizeof(Exits) ) {
            message("system", ob->GetCapName()
                    +"无处可去！", this_player() );
            return 1;
        }
        NewLocation = Exits[ random(sizeof(Exits)) ];
        NewLocation = environment(ob)->GetExit(NewLocation);
        OldLocation = base_name(environment(ob));
        message("my_action", "你把"+ob->GetCapName()+"推开了！",
                this_player() );
        message("other_action", "你被"+
                this_player()->GetCapName()+"推开了！",
                ob);
        message("other_action", this_player()->GetCapName()+"把"+
                ob->GetCapName()+"推开了！",
                environment(ob), ({ ob, this_player() }) );
        if( !ob->eventMove(NewLocation) ) {
            message("other_action", ob->GetCapName()+"被弹回了房间。", environment(ob), ob);
            message("my_action", "你被弹回了原来的位置。",
                    ob);
        } else {
            ob->eventDescribeEnvironment(0);
            if( !userp(ob) )
                call_out((: MoveBack :), 12 + random(6), ob, OldLocation);
        }
        if( ob->GetHealthPoints() > 5 )
            ob->eventReceiveDamage(this_player(), BLUNT, random(5));
        return 1;
    }
    return 0;
}

void MoveBack(object ob, string where) {
    if( !ob ) return;
    ob->eventForce("growl");
    tell_room(environment(ob),capitalize(ob->GetShort())+"愤怒地离开了。");
    ob->eventMove(where);
    tell_room(environment(ob),capitalize(ob->GetShort())+"愤怒地进来了。");
    ob->eventForce("say wtf");
}
