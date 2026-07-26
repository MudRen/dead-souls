#include <lib.h>
#include <daemons.h>
#include <dirs.h>
#include <vision.h>
#include <medium.h>
#include <terrain_types.h>
#include <damage_types.h>
#include <respiration_types.h>

inherit LIB_SHADOW;
inherit LIB_ID;

object me = this_object();
object suit;
int disguised, reporting = 1;

int SetDisguised(int i){
    if(i) disguised = 1;
    else disguised = 0;
    return disguised;
}

int GetDisguised(){
    return disguised;
}

int CheckDisguised(){
    object ob;
    if(clonep()) ob = GetShadowedObject();
    if(!ob || !disguised) return 0;
    else return 1;
}

int CheckSuit(){
    if(!suit){
        this_object()->unarbitershadow();
        return 0;
    }
    return 1;
}

varargs string GetExternalDesc(object who){
    object ob = GetShadowedObject();
    if(!clonep()) return "";
    if(CheckDisguised()) return "现存权威军事力量的仲裁者。";
    else return ob->GetExternalDesc(who);
}

varargs string GetLong(object who){
    object ob = GetShadowedObject();
    if(!clonep()) return "";
    if(CheckDisguised()) return "现存权威军事力量的仲裁者。";
    else return ob->GetLong(who);
}

string GetName(){
    object ob = GetShadowedObject();
    if(!clonep()) return "";
    if(CheckDisguised() || !ob) return "仲裁者";
    else return ob->GetName();
}

string GetCapName(){
    object ob = GetShadowedObject();
    if(!clonep()) return "";
    if(CheckDisguised()) return "仲裁者";
    else return ob->GetCapName();
}

string GetKeyName(){
    object ob = GetShadowedObject();
    if(!clonep()) return "";
    if(CheckDisguised()) return "arbiter";
    else return ob->GetKeyName();
}

string GetShort(){
    object ob = GetShadowedObject();
    if(!clonep()) return "";
    if(CheckDisguised()) return "一名仲裁者";
    else return ob->GetShort();
}

string GetRace(){
    object ob = GetShadowedObject();
    if(!clonep()) return "";
    if(CheckDisguised()) return "human";
    else return ob->GetRace();
}

int eventShadow(object whom){
    object *shadows = keys(whom->GetShadows());
    if(sizeof(shadows)){
        foreach(object shade in shadows){
            if(base_name(shade) == base_name(me)) return 0;
        }
    }
    if(base_name(previous_object()) == "/domains/town/armor/arbitersuit"
            || base_name(previous_object()) == "/domains/default/armor/arbitersuit"){
        ::eventShadow(whom);
        suit = previous_object();
        if(CheckDisguised()) whom->SetId(({"arbiter"}));
        if(CheckDisguised()) whom->cmdParseRefresh();
        return 1;
    }
    return 0;
}

int unarbitershadow(){
    object ob = GetShadowedObject();
    if(!ob) return 0;
    ob->SetId();
    ob->cmdParseRefresh();
    eventUnshadow();
}

string* parse_command_id_list() {
    string* ids = (this_object()->GetId() +
            (CheckDisguised() ? ({ "arbiter" }) : ({}) ) || ({}));
    return filter(ids, (: stringp($1) && ($1 != "") :));

}

string* parse_command_plural_id_list() {
    string* ids = (this_object()->GetId() +
            (CheckDisguised() ? ({ "arbiter" }) : ({}) ) || ({}));
    ids = filter(ids, (: stringp($1) && ($1 != "") :));
    return map(ids, (: pluralize :));
}

int GetSkillLevel(string skill) {
    object ob = GetShadowedObject();
    int ret;
    if(!clonep()) return 0;
    if(!CheckSuit()) return 0;
    if(!ob) return 0;
    if(!suit->GetActive()) return ob->GetSkillLevel(skill);
    switch(skill){
        case "melee attack" : ret = ob->GetSkillLevel(skill)+50;break;
        default :
    }
    if(ret){
        suit->eventDecrementCharge();
        return ret;
    }
    else return ob->GetSkillLevel(skill);
}

int GetCanBite(){
    return 0;
}

int GetStatLevel(string stat){
    object ob = GetShadowedObject();
    int ret;
    if(!clonep()) return 0;
    if(!CheckSuit()) return 0;
    if(!ob) return 0;
    if(!suit->GetActive()) return ob->GetStatLevel(stat);
    switch(stat){
        case "strength" : ret = ob->GetStatLevel(stat)+40;break;
        case "agility" : ret = ob->GetStatLevel(stat)+40;break;
        case "durability" : ret = ob->GetStatLevel(stat)+40;break;
        case "coordination" : ret = ob->GetStatLevel(stat)+40;break;
        default :
    }
    if(ret){
        suit->eventDecrementCharge();
        return ret;
    }
    else return ob->GetStatLevel(stat);
}

int GetMelee(){
    object ob = GetShadowedObject();
    if(!clonep()) return 0;
    if(!CheckSuit()) return 0;
    if(!ob) return 0;
    if(!suit->GetActive()) return ob->GetMelee();
    if(!(ob->GetMelee())) suit->eventDecrementCharge();
    return 1;
}

float AddStaminaPoints(mixed x) {
    float y;
    object ob = GetShadowedObject();
    if(!clonep()) return 0;
    if(!CheckSuit()) return 0;
    if(!ob) return 0;
    if(!suit->GetActive()) return ob->AddStaminaPoints(x);

    if( !intp(x) && !floatp(x) )
        error("Bad argument 1 to AddStaminaPoints().\n");
    x = abs(x);
    suit->eventDecrementCharge(x);
    return suit->GetRemainingCharge();
}

//This is a bit much
#if 0
int eventCollapse(){
    object ob = GetShadowedObject();
    if(!ob) return 0;
    if(!CheckSuit() || !suit->GetActive()) return ob->eventCollapse();
    suit->eventDecrementCharge();
    return suit->GetRemainingCharge();
}
#endif

int RemoveLimb(string limb, mixed agent){
    object ob = GetShadowedObject();
    if(!CheckSuit()) return 0;
    if(!ob) return 0;
    if(suit->GetActive()){
        suit->eventDecrementCharge();
        return 0;
    }
    return ob->RemoveLimb(limb, agent);
}

varargs mixed GetEffectiveVision(mixed location, int raw_score){
    object ob = GetShadowedObject();
    if(!CheckSuit()) return 0;
    if(!ob) return 0;
    if(suit->GetActive()){
        suit->eventDecrementCharge();
        return VISION_CLEAR;
    }
    return ob->GetEffectiveVision(location, raw_score);
}

varargs int CanBreathe(mixed args...){
    object ob = GetShadowedObject();
    int rtype;
    if(!ob) return 0;
    if(!CheckSuit()) return ob->CanBreathe(args);
    rtype = ob->GetRespiration();
    if(suit->GetActive()){
        if(rtype & R_AIR){
            suit->eventDecrementCharge();
            return 1;
        }
        if(rtype & R_WATER || rtype & R_METHANE) return 0;
    }
    return ob->CanBreathe(args);
}

void eventDescribeEnvironment(int verbose) {
    object ob = GetShadowedObject();
    object env;
    string grid, climate,filename,foo,tmp;
    int x,y,z,hud = 1;
    object *livings;
    string extra = "%^CYAN%^抬头显示器信息:%^RESET%^\n";
    mapping invisibles = ([]);
    int medium, terrain;

    extra += "剩余能量: "+to_int(percent(suit->GetRemainingCharge(),
                suit->GetMaxCharge()))+"%\n";

    if(!ob) return 0;
    if(!CheckSuit() || !suit->GetActive()) return ob->eventDescribeEnvironment(verbose);

    if( !(env = room_environment(ob)) ) {
        message("room_description", "没有环境。", this_object());
        return;
    }

    filename = file_name(env);
    livings = filter(get_livings(env), (: $1->GetInvis() :) );
    medium = env->GetMedium();
    terrain = env->GetTerrain();
    climate = env->GetClimate();
    grid = ROOMS_D->GetCoordinates(env);

    if(grid){
        hud = 1;
        extra += "全局坐标: "+grid+"\n";
    }

    foo = last_string_element(filename,"/");
    if(sscanf(foo,"%d,%d,%d", x,y,z) == 3 ||
            sscanf(foo,"%d,%d", x,y) == 2){
        hud = 1;
        extra += "本地坐标: "+x+","+y+","+z+"\n";
    }
    if(climate){
        hud = 1;
        extra += "气候: "+climate+"\n";
    }
    if(terrain){
        hud = 1;
        extra += "地形: ";
        if(terrain & T_OUTDOORS) extra += " 室外 ";
        if(terrain & T_INDOORS) extra += " 室内 ";
        if(terrain & T_ROAD) extra += " 道路 ";
        if(terrain & T_UNDERWATER) extra += " 水下 ";
        if(terrain & T_SURFACE) extra += " 水面 ";
        if(terrain & T_MIDAIR) extra += " 半空 ";
        if(terrain & T_SWAMP) extra += " 沼泽 ";
        if(terrain & T_WOODS) extra += " 森林 ";
        if(terrain & T_JUNGLE) extra += " 丛林 ";
        if(terrain & T_ROUGH) extra += " 崎岖 ";
        if(terrain & T_UNDERGROUND) extra += " 地下 ";
        if(terrain & T_SPACE) extra += " 太空 ";
        if(terrain & T_MAGMA) extra += " 岩浆 ";
        if(terrain & T_PLASMA) extra += " 等离子 ";
        if(terrain & T_PLANAR) extra += " 位面 ";
        if(terrain & T_SNOW) extra += " 雪地 ";
        if(terrain & T_SAND) extra += " 沙漠 ";
        if(terrain & T_ICE) extra += " 冰面 ";
        if(terrain & T_BIOLOGICAL) extra += " 生物 ";
        if(terrain & T_SEAFLOOR) extra += " 海底 ";
        extra += "\n";
    }

    if(medium){
        hud = 1;
        extra += "介质: ";
        switch(medium){
            case MEDIUM_LAND : extra += "陆地\n"; break;
            case MEDIUM_AIR : extra += "空气\n"; break;
            case MEDIUM_SPACE : extra += "太空\n"; break;
            case MEDIUM_WATER : extra += "水\n"; break;
            case MEDIUM_SURFACE : extra += "水面\n"; break;
            default: extra += "未知\n";
        }
    }

    if(sizeof(livings)){
        hud = 1;
        foreach(object dude in livings){
            if(!invisibles[dude->GetRace()]) invisibles[dude->GetRace()] = 1;
            else invisibles[dude->GetRace()]++;
        }
        foreach(mixed key, mixed val in invisibles){
            if(!key) continue;
            extra += "隐形的"+pluralize(key)+": "+val+"\n";
        }
    }

    ob->eventDescribeEnvironment(verbose);
    if(hud) message("system", extra, ob);
}

varargs int eventReceiveDamage(mixed agent, int type, int x, int internal, mixed limbs) {
    object ob = GetShadowedObject();
    string evidence, limb_string;

    if(!CheckSuit()) return 0;
    if(!ob) return 0;
    if(internal || !suit->GetActive()) return ob->eventReceiveDamage(agent, type, x, internal, limbs);

    if(reporting){
        string *damtypes = TYPES_D->eventCalculateTypes("damage", type);
        evidence = "动力装甲的抬头显示器发出警报:\n";
        evidence += "%^BOLD%^%^RED%^";
        if(objectp(agent)) evidence += "受到伤害！";
        if(type && sizeof(damtypes)) {
            string verboid;
            if(sizeof(damtypes) > 1) verboid = "类型为 ";
            else verboid = "类型为 ";

            evidence += " 伤害"+verboid;
            evidence += lower_case(implode(damtypes,", "));
        }

        else evidence += " 伤害类型为未知";
    }

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
    else limb_string = "。位置无法确定。";
    if(limbs) {
        evidence += "。位置: ";
        evidence += limb_string + "。";
    }
    this_object()->eventPrint(evidence+"%^RESET%^");

    this_object()->eventPrint("%^YELLOW%^能量消耗: "+x+"单位。%^RESET%^");
    suit->eventDecrementCharge(x);
    return 1;
}

int AddLead(string ammo,int number){
    return 0;
}

