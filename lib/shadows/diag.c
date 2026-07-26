#include <damage_types.h>
inherit LIB_SHADOW;

varargs int eventReceiveDamage(mixed agent, int type, int x, int internal, mixed limbs) {
    int hp, damage, damdiff;
    object ob = GetShadowedObject();
    string evidence, limb_string;
    evidence = "";
    if(objectp(agent)) evidence += "你受到了"+agent->GetKeyName()+"的伤害";
    else if(stringp(agent)) evidence += "你受到了"+agent+"的伤害";
    if(type) {
        switch(type){
            case BLUNT : evidence += ", 伤害类型为钝击";break;
            case BLADE : evidence += ", 伤害类型为利刃";break;
            case KNIFE : evidence += ", 伤害类型为刀伤";break;
            case WATER : evidence += ", 伤害类型为水伤";break;
            case SHOCK : evidence += ", 伤害类型为电击";break;
            case COLD : evidence += ", 伤害类型为冰冻";break;
            case HEAT : evidence += ", 伤害类型为灼热";break;
            case GAS : evidence += ", 伤害类型为毒气";break;
            case ACID : evidence += ", 伤害类型为酸蚀";break;
            case MAGIC : evidence += ", 伤害类型为魔法";break;
            case POISON : evidence += ", 伤害类型为毒素";break;
            case DISEASE : evidence += ", 伤害类型为疾病";break;
            case TRAUMA : evidence += ", 伤害类型为创伤";break;
            case PIERCE : evidence += ", 伤害类型为穿刺";break;
            case PSIONIC : evidence += ", 伤害类型为念力";break;
            case ANOXIA : evidence += ", 伤害类型为缺氧";break;
            case DEATHRAY : evidence += ", 伤害类型为死光";break;
            case EMOTIONAL : evidence += ", 伤害类型为情感";break;
            case SONIC : evidence += ", 伤害类型为音波";break;
            case BITE : evidence += ", 伤害类型为咬伤";break;
            case OTHER : evidence += ", 伤害类型为其他";break;
            default : evidence += ", 伤害类型为未知";break;
        }
    }
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
    else limb_string = ", 我无法判断被击中了哪里。";
    if(limbs) {
        evidence += ", 受影响的部位: ";
        evidence += limb_string + ".";
    }
    this_object()->eventForce("say "+evidence);
    hp = this_object()->GetHealthPoints();

    if(!agent) agent = this_object();
    if(!type) type = 0;
    if(!x) x = 0;
    if(!internal) internal = 0;
    if(!limbs) limbs = "";

    if(ob) ob->eventReceiveDamage(agent, type, x, internal, limbs);

    damage = this_object()->GetHealthPoints();
    damdiff = hp - damage;
    this_object()->eventForce("say 实际造成的伤害: "+damdiff);
}

int RemoveLimb(string limb, object agent){
    object ob = GetShadowedObject();
    if(!ob) return;
    if(ob->GetKeyName() == "dummy"){
        this_object()->eventForce("say 我的"+limb+"已经受到了足以切断它的伤害。"
                "不过，由于我是训练假人，我会保留它的。");
        return 1;
    }
    return ob->RemoveLimb(limb, agent);
}
