#include <lib.h>
#include <armor_types.h>
#include <size_types.h>
#include <damage_types.h>
inherit LIB_BANE;
inherit LIB_WORN_STORAGE;
object scoutshadow;
int active = 1;
int charge = 0;
int maxcharge = 3000;
int disguised = 0;
string owner;

varargs mixed GetSuitHelp(mixed who, string where);

string LongDesc(){
    string ret = "一件极先进的波利普克瓦设计装甲服，"+
        "由需要一定环境危害防护的宿主成员使用。";
    if(!active) return ret;
    if(charge < percent_of(10, maxcharge)) ret += " 上面亮起了一个%^RED%^红色%^RESET%^指示灯。";
    else if(charge < percent_of(50, maxcharge)) ret += " 上面亮起了一个%^YELLOW%^黄色%^RESET%^指示灯。";
    else if(charge < percent_of(80, maxcharge)) ret += " 上面亮起了一个%^GREEN%^绿色%^RESET%^指示灯。";
    else ret += " 上面亮起了一个%^BLUE%^蓝色%^RESET%^指示灯。";
    return ret;
}

protected void create(){
    ::create();
    SetKeyName("scout suit");
    SetId(({"suit", "armor"}));
    SetAdjectives(({"poleepkwa","scout","suit of","powered","formidable", "formidable looking"}));
    SetShort("一套波利普克瓦侦察装甲");
    SetLong((:LongDesc:));
    SetMass(500);
    SetMatching(0);
    SetBaseCost("silver",5000);
    SetArmorType(A_EXO);
    SetRestrictLimbs( ({
                "torso", "head", "neck",
                "right arm", "left arm",
                "right leg", "left leg",
                "right hand", "left hand",
                "right foot", "left foot",
                }) );
    AddSave( ({ "charge", "disguised", "owner", "maxcharge" }) );
    SetMaxCarry(500);
    SetSize(S_SOMEWHAT_LARGE);
    SetProtection(BLUNT,20);
    SetProtection(BLADE,20);
    SetProtection(KNIFE,20);
    SetDamagePoints(100);
    SetWear((: GetSuitHelp :));
    AddItem( ({"light","status light"}), "A status light.");
    set_heart_beat(5);
}

void init(){
    ::init();
    add_action("GetSuitHelp", "help");
}

varargs mixed GetSuitHelp(mixed who, string where){
    string ret, ret2, str;
    object env;
    if(!who){
        return 0;
    }
    if(stringp(who)){
        str = who;
        who = this_player();
    }
    else str = GetKeyName();
    env = environment(who);
    if(query_verb() == "wear" || (str && answers_to(str, this_object()))){
        if(environment() == who){
            ret = "装甲的平视显示器噼啪作响地亮了起来，显示：\n ";
            ret += "%^B_BLACK%^CYAN%^";
            ret2 = "从宿主你获得身份。从众多中"+
                "我们是宿主。你被保护以服务。用这套装甲服务宿主。"+
                "这套装甲保护你。用它来服务。"+
                "\n当装甲灯为黄色或红色时，躲藏。"
                "\n当装甲灯为绿色或蓝色时，服务。"
                "\n你的黑色汁液让装甲运转。"
                "\n装甲从你身上吸取黑色汁液。"
                "\n当它充满黑色汁液时，灯为蓝色。"
                "\n当灯亮着时你可以呼吸。"
                "\n当灯亮着时你可以承受巨大伤害。"
                "\n当灯亮着时你看得清楚。"
                "\n当灯亮着时你不会生病。";
            "\n你不能与他人交换装甲。";
            if(query_verb() == "wear" && !GetWorn()){
                who->eventPrint("你穿戴上了"+GetShort()+"。");
                if(env) tell_room(env, who->GetName()+" wears "+
                        GetShort()+".", ({who}));
            }
            ret2 = translate(ret2, who->GetLanguageLevel("Poleepkwa"));
            who->eventPrint(ret+ret2+"%^RESET%^");
            return 1;
        }
    }
    return 0;
}

mixed eventEquip(object who, string* limbs){
    mixed success = ::eventEquip(who, limbs);
    scoutshadow = new("/shadows/pscout");
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
    if(perc < 2){
        if(living(env) && creatorp(env)){
            env->eventPrint("你的创造者力量魔法般地为"+
                    remove_article(GetShort())+"充能了。");
            charge = maxcharge;
            return charge;
        }
        tell_object(env,remove_article(GetShort())+"大声哔哔作响！");
        return charge;
    }

    if(perc < 2){
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
        //if(scoutshadow) scoutshadow->eventUnshadow();
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

void heart_beat(){
    int notify;
    string str, envname;
    object env = environment();
    object room = room_environment();
    if(!env || !room) return;
    envname = env->GetKeyName();
    if(owner && GetWorn() && envname != owner){
        tell_object(env, "装甲发出短暂的嘎吱声和嗡嗡声。");
        if(active) active = 0;
        return;
    }
    if(active && !GetWorn()){
        tell_room(env, remove_article(GetShort())+
                "发出嗡嗡声。");
        active = 0;
    }
    else if(GetWorn() && charge < maxcharge){
        int fuel;
        fuel = env->GetMagicPoints();
        if(fuel < 5){
            if(!charge && active){
                active = 0;
                if(environment(env)){
                    tell_room(environment(env), env->GetName()+"'s "+
                            "powered suit whines.", ({env}));
                    env->eventPrint("你的动力装甲发出嗡嗡声。");
                }
            }
        }
        else {
            env->AddMagicPoints(-5);
            charge += 5;
            //env->eventPrint("adding 5. charge: "+charge+". "+
            //  (active ? "active" : "inactive"));
            if(!owner) owner = env->GetKeyName();
        }
    }
    if(GetWorn() && !active && charge > 9){
        active = 1;
        if(environment(env)){
            tell_room(environment(env), env->GetName()+"'s "+
                    "powered suit chirps.", ({env}));
            env->eventPrint("你的动力装甲发出哔哔声。");
        }
    }
}

//Every 100 points of damage received by the suit, it lowers
//the max charging capacity by 100.
void eventDeteriorate(int type){
    object env = environment();
    if(maxcharge > 100){
        if(active){
            if(env) env->eventPrint("你的动力装甲发出刺耳的嗡嗡声，"+
                    "指示灯短暂变暗。");
        }
        maxcharge -= 100;
    }
    ::eventDeteriorate(type);
}

int eventReceiveDamage(mixed agent, int type, int amt, int i, mixed* l){
    if(!active || charge < 20){
        return ::eventReceiveDamage(agent, type, amt, i, l);
    }
    return 0;
}

