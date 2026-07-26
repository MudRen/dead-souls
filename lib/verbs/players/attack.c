/*    /verbs/players/attack.c
 *    from the Dead Souls Mud Library
 *    a very violent command
 *    created by Descartes of Borg 960512
 *    Version: @(#) attack.c 1.3@(#)
 *    Last Modified: 96/10/20
 */

#include <lib.h>
#include <daemons.h>
#include <position.h>
#include "include/attack.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("attack");
    SetRules("LVS", "only LVS","LVS only");
    SetSynonyms("kill", "smite", "waste", "hit", "gank");
    SetErrorMessage("攻击谁？");
    SetHelp("用法：attack <生物>\n"
            "      attack all of <生物>\n"
            "      attack all\n\n"
            "此命令使用任何已装备的武器或你的空手与一个或一群生物发起战斗。"
            "请非常小心，不要在房间内有其他玩家时使用 \"attack all\"，否则你将犯有企图杀害玩家的罪行。\n"
            "另见：wimpy, ignore, target");
}

varargs mixed can_attack_liv(object target) {
    int pos = this_player()->GetPosition();

    if( this_player()->GetParalyzed() ) {
        return "你动弹不得！";
    }
    if( pos == POSITION_SITTING || pos == POSITION_LYING &&
            !RACES_D->GetLimblessCombatRace(this_player()->GetRace()) ){
        return "你在那个姿势下无法攻击！";
    }
    if( this_player() && environment(this_player()) &&
            environment(this_player())->GetProperty("no attack") ) {
        return "一股神秘的力量阻止了你的恶意。";
    }
    return 1;
}

mixed can_attack_only_liv(object target){
    return can_attack_liv(target);
}

mixed can_attack_liv_only(object target){
    return can_attack_liv(target);
}

mixed do_attack_liv(object target) {
    return do_attack_lvs(({ target }));
}

mixed do_attack_only_liv(object target){
    return do_attack_lvs(({ target }), 1);
}

mixed do_attack_liv_only(object target){
    return do_attack_lvs(({ target }), 1);
}

varargs mixed do_attack_lvs(mixed *targets, int exclusive) {
    object *obs, *tmpobs;
    object *noattack;
    string tmp;

    if(this_player()->GetDying()) return 0;

    noattack = ({});
    tmpobs = ({});
    obs = filter(targets, (: objectp($1) && !($1->GetInvis()) :));
    targets -= ({ this_player() });

    if(!sizeof(targets)){
        write("没有可以攻击的目标。");
        return 1;
    }

    if( !sizeof(obs) ) {
        mixed *ua;

        ua = unique_array(targets, (: $1 :));
        foreach(string *lines in ua) this_player()->eventPrint(lines[0]);
        return 1;
    }
    if(exclusive){
        foreach(object entity in get_livings(environment(this_player()))){
            if(member_array(entity,obs) == -1) noattack += ({ entity });
        }
        if(sizeof(noattack)) this_player()->AddNonTargets(noattack);
    }
    foreach(object subobj in obs){
        if(subobj == this_player()) continue;
        if(member_array(this_player(),subobj->GetEnemies()) != -1 &&
                member_array(subobj,this_player()->GetNonTargets()) != -1){
            write("你已经在和"+subobj->GetName()+"战斗了！");
        }
        else {
            mixed attackable = subobj->CanAttack(this_player());
            if(intp(attackable) && attackable) tmpobs += ({ subobj });
            else if(stringp(attackable)) write(attackable);
        }
    }

    obs = tmpobs;
    if(!sizeof(obs)) return 1;

    this_player()->SetAttack(obs);
    tmp = item_list(obs);
    obs->eventPrint(this_player()->GetName() + "攻击了你！");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "攻击了" + tmp + "！",
            ({ this_player(), obs... }));
    this_player()->eventPrint("你向" + tmp + "冲去。");
    return 1;
}
