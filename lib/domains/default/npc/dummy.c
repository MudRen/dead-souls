#include <lib.h>
#include <daemons.h>
#include <damage_types.h>
inherit LIB_NPC;

protected void create(){
    npc::create();
    SetKeyName("dummy");
    SetId( ({"dummy","mokujin","buster"}) );
    SetShort("一个训练假人");
    SetLong("这是一个神奇的陪练伙伴。它由原木制成，被切割成人类头部、躯干和四肢的比例。原木由链条制成的关节连接在一起。");
    SetPacifist(1);
    SetBodyComposition("wood");
    SetInventory(([
                ]));
    SetLevel(10);
    SetRace("dummy");
    SetClass("fighter");
    SetGender("neuter");
    SetMaxHealthPoints(9000);
    SetHealthPoints(9000);
}

varargs int eventReceiveDamage(object agent, int type, int x, int internal, mixed limbs) {
    int hp, damage, damdiff;
    string evidence, limb_string;
    evidence = "";
    if(objectp(agent)) evidence += "我受到了来自"+agent->GetKeyName()+"的伤害";
    else evidence += "我受到了来自"+agent+"的伤害";
    evidence += ".";
    if(type) {
        string *damtypes = TYPES_D->eventCalculateTypes("damage", type);
        if(type && sizeof(damtypes)) {
            string verboid;
            if(sizeof(damtypes) > 1) verboid = "s are ";
            else verboid = " is ";

            evidence += " Damage type"+verboid;
            evidence += implode(damtypes,", ");
        }
        else evidence += " 伤害类型未知";
    }
    if(x) evidence += "，原始伤害为"+x;
    if(internal) evidence += "，内部变量为"+internal;
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
    else limb_string = "，我无法判断被击中了哪里。";
    if(limbs) { 
        evidence += "，受影响的身体部位：";
        evidence += limb_string + ".";
    }
    eventForce("say "+evidence);
    hp = GetHealthPoints();

    if(!agent) agent = this_object();
    if(!type) type = 0;
    if(!x) x = 0;
    if(!internal) internal = 0;
    if(!limbs) limbs = "";

    ::eventReceiveDamage(agent, type, x, internal, limbs);

    damage = GetHealthPoints();
    damdiff = hp - damage;
    eventForce("say 实际造成的伤害："+damdiff);
    AddHP(damdiff+1);
}

int RemoveLimb(string limb, object agent){
    if(query_verb() == "eval" || query_verb() == "amputate" ||
            query_verb() == "call"){
        return ::RemoveLimb(limb, agent);
    }
    eventForce("say 我的"+limb+"受到了足以切断它的伤害。不过，由于我是一个训练假人，我会保留它的。");
    return 1;
}

void init(){
    ::init();
}
