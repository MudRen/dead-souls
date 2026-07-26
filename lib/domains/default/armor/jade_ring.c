#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
object ringshadow;

string LongRet(mixed whom){
    string ret = "一枚绿色戒指， glowing with unearthly power。";
    if(!whom || !objectp(whom) || !living(whom)) whom = this_player();
    if(creatorp(whom) ||
            member_group(whom,"TEST")){
        ret += "\n要启用伤害保护，输入：protection on";
        ret += "\n要启用伤害报告，输入：reporting on";
        ret += "\n要让一个生物报告其伤害：enablereport <名称>";
        ret += "\n要让它停止报告其伤害：disablereport <名称>\n";
    }
    return ret;
}

protected void create(){
    armor::create();
    SetKeyName("jade ring");
    SetId(({"ring","ward","jade"}));
    SetAdjectives( ({"jade","green","power","powerful"}) );
    SetShort("一枚翡翠戒指");
    SetLong( (: LongRet :) );
    SetMass(1);
    SetBaseCost("silver",5000);
    SetArmorType(A_RING);
}

void init(){
    armor::init();
    add_action("SetProtection", "protection");
    add_action("SetReporting", "reporting");
    add_action("SetNPCReporting", "enablereport");
    add_action("UnsetNPCReporting", "disablereport");
}

mixed CanEquip(object who, string* limbs){
    if(who && !creatorp(who) && !member_group(who,"TEST")){
        return " somehow it just won't go on。 Strange, isn't it?";
        return 0;
    }
    else return armor::CanEquip(who, limbs);
}

int eventRegenerate(object who){
    int i;
    string *stumps;
    stumps=who->GetMissingLimbs();
    if(sizeof(stumps)) {
        for(i=0;i<sizeof(stumps);i++){
            who->RestoreLimb(stumps[i]);
        }
    }
    return 1;
}

int PerformHeal(){
    object who;
    mapping stumps;
    string *limb_arr = ({});
    int i, mhp, msp, mmp, self;

    who = this_player();

    mhp = who->GetMaxHealthPoints();
    msp = who->GetMaxStaminaPoints();
    mmp = who->GetMaxMagicPoints();
    who->AddHP(mhp);
    who->AddStaminaPoints(msp);
    who->AddMagicPoints(mmp);
    if(who->GetPoison() > 0) who->AddPoison(0 - who->GetPoison());
    eventRegenerate(who);
    limb_arr = who->GetLimbs();
    foreach(string limb in limb_arr) {
        who->HealLimb(limb);
    }
    return 1;
}

int CheckRing(){
    if(environment() != this_player()) return 0;
    if(!(this_object()->GetWorn())) return 0;
    if(!creatorp(environment()) &&
            !member_group(environment(),"TEST")) return -1;
    return 1;
}

int SetNPCReporting(string name){
    object *sombras = ({});
    object ob;
    if(!CheckRing() || !ringshadow){
        write("戒指 must be worn by you in order to access its power。");
        return 1;
    }
    if(CheckRing() == -1){
        write("戒指's power can only be harnessed by special people。 That means, \"not you\"。");
        return 1;
    }
    if(!(ob = present(name,environment(this_player())))){
        write("这里没有这种生物。");
        return 1;
    }
    sombras = keys(ob->GetShadows());
    if(sizeof(sombras)){
        foreach(object element in sombras){
            if(base_name(element) == "/shadows/diag"){
                write("那个生物 already reporting its damage status。");
                return 1;
            }
        }
    }
    new("/shadows/diag")->eventShadow(ob);
    write("伤害报告已启用 for "+name+"。");
    return 1;
}

int UnsetNPCReporting(string name){
    object *sombras = ({});
    object ob;
    int stat = 0;
    if(!CheckRing() || !ringshadow){
        write("The ring must be worn by you in order to access its power.");
        return 1;
    }
    if(CheckRing() == -1){
        write("The ring's power can only be harnessed by special people. That means, \"not you\".");
        return 1;
    }
    if(!(ob = present(name,environment(this_player())))){
        write("No such creature is here.");
        return 1;
    }
    sombras = keys(ob->GetShadows());
    if(sizeof(sombras)){
        foreach(mixed element in sombras){
            if(element && objectp(element) && base_name(element) == "/shadows/diag"){
                stat = 1;
                element->eventUnshadow();
            }
        }
    }
    if(!stat) write("那个生物没有启用报告。");
    else write("伤害报告已禁用 for "+name+"。");
    return 1;
}

int SetProtection(string str){
    int booly = 0;
    if(!CheckRing() || !ringshadow){
        write("The ring must be worn by you in order to access its power.");
        return 1;
    }
    if(CheckRing() == -1){
        write("The ring's power can only be harnessed by special people. That means, \"not you\".");
        return 1;
    }
    if(str == "on") booly=1;
    write("你将戒指的保护设置为："+(booly ? "开启" : "关闭")+"。");
    if(ringshadow) ringshadow->JadeProtection(booly);
    return 1;
}

int SetReporting(string str){
    int booly = 0;
    if(!CheckRing() || !ringshadow){
        write("The ring must be worn by you in order to access its power.");
        return 1;
    }
    if(CheckRing() == -1){
        write("The ring's power can only be harnessed by special people. That means, \"not you\".");
        return 1;
    }
    if(str == "on") booly=1;
    write("你将戒指的报告设置为："+(booly ? "开启" : "关闭")+"。");
    if(ringshadow) ringshadow->JadeReporting(booly);
    return 1;
}

mixed eventEquip(object who, string* limbs){
    int ok = 0;
    mixed success = armor::eventEquip(who, limbs);
    if(!ringshadow){
        object *sombras = keys(who->GetShadows());
        ok = 1;
        ringshadow = new("/shadows/ring");
        foreach(object element in sombras){
            if(base_name(element) == base_name(ringshadow)){
                ok = 0;
                if(ringshadow) destruct(ringshadow);
                ringshadow = element;
            }
        }
    }
    if(success){
        PerformHeal();
        if(ok){
            if(ringshadow) ringshadow->eventShadow(who);
            if(ringshadow) ringshadow->JadeProtection(1);
        }
    }
    else if(ringshadow) destruct(ringshadow);
    return success;
}

varargs mixed eventUnequip(object who) {
    mixed success;
    if(!who) who = this_player();
    success = armor::eventUnequip(who);
    if(success){
        if(ringshadow) ringshadow->eventUnshadow(ringshadow);
    }
    return success;
}
