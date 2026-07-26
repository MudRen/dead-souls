#include <lib.h>
#include <armor_types.h>
#include <size_types.h>
#include <damage_types.h>
inherit LIB_BANE;
inherit LIB_WORN_STORAGE;
object scoutshadow;
int active = 1;
int charge = 2000;
int maxcharge = 2000;
int disguised = 0;

varargs mixed GetSuitHelp(mixed who, string where);

protected void create(){
    ::create();
    SetKeyName("scout suit");
    SetId(({"suit", "armor"}));
    SetAdjectives(({"scout","suit of","powered","formidable", "formidable looking"}));
    SetShort("一套侦察兵动力装甲");
    SetLong("一套外观威武的动力装甲，由现存权威力量使用。"+
            "这一套似乎是侦察兵型号的。");
    SetMass(700);
    SetMatching(0);
    SetBaseCost("silver",5000);
    SetArmorType(A_CUSTOM);
    SetRestrictLimbs( ({
                "torso", "head", "neck",
                "right arm", "left arm",
                "right leg", "left leg",
                "right hand", "left hand",
                "right foot", "left foot",
                }) );
    AddSave( ({ "charge", "disguised" }) );
    SetMaxCarry(500);
    SetSize(S_HUMAN_SIZED);
    SetWear((: GetSuitHelp :));
}

void init(){
    ::init();
    add_action("GetSuitHelp", "help");
}

varargs mixed GetSuitHelp(mixed who, string where){
    string ret, ret2, str;
    object env;
    if(!who) return 0;
    if(stringp(who)){
        str = who;
        who = this_player();
    }
    else str = GetKeyName();
    env = environment(who);
    if(query_verb() == "wear" || (str && answers_to(str, this_object()))){
        if(environment() == who && charge){
            ret = "装甲的平视显示器噼啪作响地亮了起来，显示：\n ";
            ret += "%^GREEN%^";
            ret2 = "这套装甲让你，尊贵的侦察兵，能够在危险地形中"+
                "以最小的不便行走。为了履行你对现存权威力量的职责，"+
                "这套装甲提供以下能力增强：\n\n"+
                "* 在所有光线条件下拥有良好视野。\n"+
                "* 持续供应可呼吸空气。\n"+
                "* 大幅增强力量、协调性、敏捷性和耐久性。\n"+
                "* 大幅增强徒手战斗能力。\n"+
                "* 平视显示器显示关键环境信息。\n"+
                "* 在可用时显示网格坐标信息。\n"+
                "* 免受所有形式的外部伤害。\n"+
                "* 免疫疾病。\n\n"+
                "注意，一旦装甲的能量等级降为零，所有增强功能将不可用。"+
                "请注意，作为侦察兵，你的仲裁者依赖你卓越的判断力来"+
                "脱离不和谐并报告此类情况以转交谈判部队。%^RESET%^";
            if(query_verb() == "wear" && !GetWorn()){
                who->eventPrint("你穿戴上了"+GetShort()+"。");
                if(env) tell_room(env, who->GetName()+" wears "+
                        GetShort()+".", ({who}));
            }
            ret2 = translate(ret2, who->GetLanguageLevel("English"));
            who->eventPrint(ret+ret2);
            return 1;
        }
    }
    return 0;
}

mixed eventEquip(object who, string* limbs){
    mixed success = ::eventEquip(who, limbs);
    scoutshadow = new("/shadows/scout");
    if(scoutshadow) scoutshadow->SetDisguised(disguised);
    if(success){
        if(scoutshadow) scoutshadow->eventShadow(who);
    }
    else if(scoutshadow) destruct(scoutshadow);
    return success;
}

varargs mixed eventUnequip(object who) {
    mixed success;
    if(!who) who = this_player();
    success = ::eventUnequip(who);
    if(success){
        if(scoutshadow) who->unscoutshadow();
    }
    return success;
}

int GetActive(){
    if(!charge) return 0;
    return active;
}

int SetActive(int i){
    if(i) active = 1;
    else active = 0;
    return active;
}

int eventDecrementCharge(int i){
    int perc;
    object env = environment();
    if(!env) return 0;

    if(!GetWorn()) return 0;
    if(previous_object() != scoutshadow) return 0;
    if(charge < 1) charge = 0;
    else {
        if(!i) charge--;
        else charge -= i;
        if(charge < 0) charge = 0;
    }

    perc = to_int(percent(charge, maxcharge));
    if(perc < 10){
        if(living(env) && creatorp(env)){
            env->eventPrint("你的创造者力量魔法般地为"+
                    remove_article(GetShort())+"充能了。");
            charge = maxcharge;
            return charge;
        }
        tell_object(env,remove_article(GetShort())+"大声哔哔作响！");
        return charge;
    }

    if(perc < 20){
        if(living(env) && creatorp(env)){
            env->eventPrint("你的创造者力量魔法般地为"+
                    remove_article(GetShort())+"充能了。");
            charge = maxcharge;
            return charge;
        }
        tell_object(env,remove_article(GetShort())+"轻声哔哔作响。");
        return charge;
    }

    return charge;
}

int GetRemainingCharge(){
    if(!charge || !GetWorn()){
        if(scoutshadow) scoutshadow->eventUnshadow();
        return 0;
    }
    return charge;
}

int GetMaxCharge(){
    return maxcharge;
}

int SetCharge(int i){
    charge = i;
    return charge;
}

int SetMaxCharge(int i){
    maxcharge = i;
    return maxcharge;
}

string* GetBane(){
    if(GetActive()) return ({ "all" });
    else return ({});
}

string* QueryBane(){
    if(GetActive()) return ({ "all" });
    else return ({});
}
