#include <lib.h>
#include <daemons.h>
#include <damage_types.h>
inherit LIB_NPC;

protected void create(){
    npc::create();
    SetKeyName("dummy");
    SetId( ({"dummy","mokujin"}) );
    SetShort("训练假人");
    SetLong("这是一个魔法陪练伙伴。它由原木制成，切割成人类头部、躯干和四肢的比例。原木由链条制成的关节连接在一起。");
    SetPacifist(1);
    SetBodyComposition("wood");
    SetInventory(([
                ]));
    SetLevel(10);
    SetRace("golem");
    SetNativeLanguage("english");
    SetClass("fighter");
    SetGender("neuter");
    SetMaxHealthPoints(9000);
    SetHealthPoints(9000);
}
varargs int eventReceiveDamage(object agent, int type, int x, int internal, mixed limbs) {
    int hp, damage, damdiff;
    string evidence, limb_string;
    evidence = "";
    if(objectp(agent)) evidence += "I receive damage from "+agent->GetKeyName();
    else evidence += "I receive damage from "+agent;
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
        else evidence += " Damage type is UNKNOWN";
    }
    if(x) evidence += ", raw damage is "+x;
    if(internal) evidence += ", internal variable is "+internal;
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
    else limb_string = ", and I can't tell where I'm hit. ";
    if(limbs) { 
        evidence += ", body part(s) affected: ";
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
    eventForce("say actual damage done: "+damdiff);
    AddHP(damdiff+1);
}

int RemoveLimb(string limb, object agent){
    eventForce("say My "+limb+" has received enough damage to sever it. "
            "However, since I am a training dummy, I'll be keeping it.");
    return 1;
}

void init(){
    ::init();
}
