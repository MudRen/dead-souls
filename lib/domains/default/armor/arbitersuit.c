#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_BANE;
inherit LIB_WORN_STORAGE;
object arbitershadow;
int active = 1;
int charge = 20000;
int maxcharge = 20000;
int disguised = 0;

varargs mixed GetSuitHelp(mixed who, string where);

protected void create(){
    ::create();
    SetKeyName("arbiter suit");
    SetId(({"suit", "armor"}));
    SetAdjectives(({"arbiter","suit of","powered","formidable", "formidable looking"}));
    SetShort("一套仲裁者动力装甲");
    SetLong("一套外观威武的动力装甲，由现存权威力量使用。"+
            "这一套似乎是仲裁者型号的。");
    SetMass(7000);
    SetMatching(0);
    SetBaseCost("silver",50000);
    SetArmorType(A_CUSTOM);
    SetRestrictLimbs( ({
                "torso", "head", "neck",
                "right arm", "left arm",
                "right leg", "left leg",
                "right hand", "left hand",
                "right foot", "left foot",
                }) );
    AddSave( ({ "charge", "disguised" }) );
    SetMaxCarry(5000);
    SetWear((: GetSuitHelp :));
}

void init(){
    ::init();
    add_action("GetSuitHelp", "help");
}

varargs mixed GetSuitHelp(mixed who, string where){
    string ret, str;
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
            ret += "%^GREEN%^这套装甲让你，强大的仲裁者，能够在危险地形中"+
                "以最小的不便行走。为了履行你对现存权威力量的职责，"+
                "这套装甲提供以下能力增强：\n\n"+
                "* 在所有光线条件下拥有良好视野。\n"+
                "* 持续供应可呼吸空气。\n"+
                "* 大幅增强力量、协调性、敏捷性和耐久性。\n"+
                "* 大幅增强徒手战斗能力。\n"+
                "* 平视显示器显示关键环境信息。\n"+
                "* 在可用时显示网格坐标信息。\n"+
                "* 免受所有形式的外部伤害。\n"+
                "* 免疫疾病。\n"+
                "\n注意，一旦装甲的能量等级降为零，所有增强功能将不可用。%^RESET%^";
            who->eventPrint("你穿戴上了"+GetShort()+"。");
            if(env) tell_room(env, who->GetName()+" wears "+
                    GetShort()+".", ({who}));
            return 1;
        }
    }
    return 0;
}

mixed eventEquip(object who, string* limbs){
    mixed success = ::eventEquip(who, limbs);
    arbitershadow = new("/shadows/arbiter");
    if(arbitershadow) arbitershadow->SetDisguised(disguised);
    if(success){
        if(arbitershadow) arbitershadow->eventShadow(who);
    }
    else if(arbitershadow) destruct(arbitershadow);
    return success;
}

varargs mixed eventUnequip(object who) {
    mixed success;
    if(!who) who = this_player();
    success = ::eventUnequip(who);
    if(success){
        if(arbitershadow) who->unarbitershadow();
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
    if(previous_object() != arbitershadow) return 0;
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
        if(arbitershadow) arbitershadow->eventUnshadow();
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
