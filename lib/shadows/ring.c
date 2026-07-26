#include <daemons.h>
#include <damage_types.h>
inherit LIB_SHADOW;
int reporting = 1;
int protecting = 1;

varargs int eventReceiveDamage(mixed agent, int type, int x, int internal, mixed limbs) {
    int stamina, fatigue, hp, damage, damdiff;
    object ob = GetShadowedObject();
    string evidence, limb_string;
    if(reporting){
        string *damtypes = TYPES_D->eventCalculateTypes("damage", type);
        evidence = "%^BOLD%^%^RED%^";

        if(objectp(agent)) evidence += "你受到了"+agent->GetKeyName()+"的伤害";
        else if(stringp(agent)) evidence += "你受到了"+agent+"的伤害";
        evidence +=".";

        if(type && sizeof(damtypes)) {
            string verboid;
            if(sizeof(damtypes) > 1) verboid = "s are ";
            else verboid = " is ";

            evidence += " 伤害"+verboid;
            evidence += lower_case(implode(damtypes,", "));
        }
        else evidence += " 伤害类型为未知";

        if(x) evidence += ", 原始伤害为 "+x;
        if(internal) evidence += ", 内部变量为 "+internal;
        if(limbs) {
            if(stringp(limbs)) limb_string = limbs;
            else if(arrayp(limbs)) {
                if(stringp(limbs[0])) limb_string = implode(limbs,", ");
                else if(objectp(limbs[0])){
                    foreach(object limb in limbs){
                        limb_string += limb->GetKeyName()+", ";
                    }
                }
            }
        }
        else limb_string = ", 你无法判断被击中了哪里。";
        if(limbs) {
            evidence += ", 受影响的部位: ";
            evidence += limb_string + ".";
        }
        this_object()->eventPrint(evidence+"%^RESET%^");
        hp = this_object()->GetHealthPoints();
        stamina =  this_object()->GetStaminaPoints();

        if(!agent) agent = this_object();
        if(!type) type = 0;
        if(!x) x = 0;
        if(!internal) internal = 0;
        if(!limbs) limbs = "";

        if(x > this_object()->GetHealthPoints() &&
                !(this_object()->GetGodMode()) ){
            this_object()->eventPrint("%^RED%^这可能是一个致命的打击。"+
                    "戒指的安全协议阻止了\"实际伤害\"的计算。%^RESET%^");
            return 1;
        }

        if(ob) ob->eventReceiveDamage(agent, type, x, internal, limbs);

        damage = this_object()->GetHealthPoints();
        fatigue = stamina - this_object()->GetStaminaPoints();
        damdiff = hp - damage;
        this_object()->eventPrint("%^RED%^实际伤害: "+damdiff+"%^RESET%^");
        this_object()->eventPrint("%^YELLOW%^耐力消耗: "+fatigue+"%^RESET%^");
        if(protecting && ob){
            ob->AddHP(damdiff+1);
            this_object()->AddStaminaPoints(fatigue+1);
        }
    }
    else if(!protecting && ob) 
        return ob->eventReceiveDamage(agent, type, x, internal, limbs);
    return 1;
}

int RemoveLimb(string limb, object agent){
    object ob = GetShadowedObject();
    if(!ob) return 0;
    if(protecting){
        this_object()->eventPrint("你已经受到了足以切断它的伤害。"+
                "然而，戒指的保护阻止了这一切。");
        return 1;
    }
    else return ob->RemoveLimb(limb, agent);
}

int AddHP(int hp){
    object ob = GetShadowedObject();
    if(protecting && hp < 0){
        if(reporting)
            this_object()->eventPrint(identify(previous_object())+"试图扣除"+
                    abs(hp)+"点生命值。戒指的保护阻止了这一行为。");
        return 1;
    }
    if(reporting){
        string operation = "增加";
        if(hp < 0) operation = "减少";
        this_object()->eventPrint(identify(previous_object())+"试图"+
                operation+abs(hp)+"点生命值。");
    }
    if(ob) return ob->AddHP(hp);
    else return 1;
}

int JadeProtection(int i){
    object ob = GetShadowedObject();
    if(!this_player()) return 0;
    if(!ob || !(this_player() == ob )) return 0;
    protecting = i;
    return protecting;
}

int JadeReporting(int i){
    object ob = GetShadowedObject();
    if(!this_player()) return 0;
    if(!ob || !(this_player() == ob )) return 0;
    reporting = i;
    return reporting;
}

int eventUnshadow(){
    object ob = GetShadowedObject();
    if(!this_player()) return 0;
    if(!ob || !(this_player() == ob )) return 0;
    return ::eventUnshadow();
}
