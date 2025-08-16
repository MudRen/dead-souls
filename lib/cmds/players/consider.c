#include <lib.h>
#include <damage_types.h>

inherit LIB_DAEMON;

int eventConsider(object whom, object opponent){
    int score = 0;
    int tmp = 0;
    int protection = 0;
    string *attack_types = ({});
    object *dam_types = ({});
    object *weapons = filter(all_inventory(whom), (: $1->GetWielded() :));
    object *enemy_armor = filter(all_inventory(opponent), (: $1->GetWorn() :));
    enemy_armor = filter(enemy_armor, (: !($1->GetWielded()) :) );

    if(sizeof(weapons)){
        foreach(object weapon in weapons){
            if(weapon->GetWeaponType() && whom->GetSkill(weapon->GetWeaponType()+" attack")){
                attack_types += ({ weapon->GetWeaponType() });
                score += ( whom->GetSkill(weapon->GetWeaponType()+" attack")["level"] ) * 3;
            }
            if(weapon->GetClass())
                score += ( weapon->GetClass() ) * 6;
            if(weapon->GetHands() > 1) {
                if(!(whom->GetSkill("multi-hand"))) score /= 3;
            }
        }
        if(sizeof(weapons) >1) {
            if(!(whom->GetSkill("multi-weapon"))) score /= 3;
        }
    }

    else if((whom->GetMelee())) {
        if(whom->GetSkill("melee attack"))
            score += (((whom->GetSkill("melee attack")["level"]) * 3)); 
    }
    if(!sizeof(attack_types)) attack_types = ({"blunt"});
    foreach(string Type in attack_types){
        int DamType = 0;
        int tmp_prot = 0;
        object *qual_armor = ({});

        switch(Type){
            case "blade" : DamType = BLADE; break;
            case "blunt" : DamType = BLUNT; break;
            case "knife" : DamType = KNIFE; break;
            case "water" : DamType = WATER; break;
            case "shock" : DamType = SHOCK; break;
            case "cold" : DamType = COLD; break;
            case "heat" : DamType = HEAT; break;
            case "gas" : DamType = GAS; break;
            case "acid" : DamType = ACID; break;
            case "magic" : DamType = MAGIC; break;
            case "poison" : DamType = POISON; break;
            case "disease" : DamType = DISEASE; break;
            case "trauma" : DamType = TRAUMA; break;
            default : DamType = BLUNT; break;
        }

        foreach(object armor in enemy_armor){
            tmp_prot += armor->GetProtection(DamType);
            if(armor->GetProtection(DamType)) qual_armor += ({ armor });
        }
        if(sizeof(qual_armor)) protection += tmp_prot / sizeof(qual_armor);
        tmp_prot = 0;
        DamType = 0;
    }

    score += whom->GetStatLevel("speed") * 2;
    score += whom->GetStatLevel("strength") * 3;
    score += whom->GetMaxHealthPoints() / 15;
    score += protection;

    return score;
}

mixed cmd(string str) {
    object thing;
    int totalscore, myscore, theirscore;

    if(!str){
        write("考虑什么？");
        return 1;
    }
    if(!(thing = present(str,environment(this_player())))){
        write("那东西不在这里。");
        return 1;
    }
    if(!living(thing)){
        write("那不是活物。");
        return 1;
    }

    theirscore = eventConsider(thing, this_player());
    myscore = eventConsider(this_player(), thing);

    totalscore = myscore - theirscore;
    if(totalscore > 100) write("小菜一碟。");
    else if(totalscore > 80) write("毫无问题。");
    else if(totalscore > 60) write("非常容易。");
    else if(totalscore > 40) write("相当容易。");
    else if(totalscore > 20) write("你大概会没事的。");
    else if(totalscore > 0) write("势均力敌。");
    else if(totalscore > -20) write("需要努力。");
    else if(totalscore > -40) write("一场硬仗。");
    else if(totalscore > -60) write("重大挑战。");
    else if(totalscore > -80) write("不明智的选择。");
    else if(totalscore > -100) write("真的很糟糕的主意。");
    else write("自杀行为。");
    return 1;
}

string GetHelp() {
    return ("语法：consider <生物>\n\n"
            "让你了解击败一个生物的难度。评估相对实力、技能、武器、"
            "护甲、等级、生命值等。最终的比较可能不太有用，因为战斗中的变化（如"
            "对手更换武器）或不寻常的等级或保护物品（如魔法护甲）可能"
            "没有被考虑在内。");
}
