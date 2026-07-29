#include <lib.h>
#include <damage_types.h>
#include <position.h>

inherit LIB_SENTIENT;
inherit LIB_ACTIVATE;
int active, ammo = 1000;

int eventShootDude(object ob){
    int dam, numlimbs;
    string limbname, str;
    string *limbs;
    if(!environment()) return 0;
    str = ob->GetName();
    if(!ammo){
        tell_room(environment(),"炮塔发出咔嗒声。");
        active = 0;
        return 0;
    }
    tell_object(this_object(),"你向"+ob->GetName()+"开火！");
    tell_room(environment(),"炮塔向"+ob->GetName()+"开火！",
            ({this_object(),ob}));
    tell_object(ob,"炮塔向你开火！");
    ammo--;
    if(random(100) < 10) return 1;
    limbs=ob->GetLimbs();
    numlimbs=sizeof(limbs);
    limbname = limbs[random(numlimbs-1)]; 
    tell_room(environment(this_object()),
            "子弹击中了"+
            capitalize(str)+"的"+limbname+"！\n",ob);
    tell_object(ob,"子弹击中了你的"+limbname+"！\n");
    ob->SetAttack(this_agent());
    if(!present("firearms_wound",ob)){
        new(LIB_WOUND)->eventMove(ob);
    }
    ob->AddLead("gunshot_wounds", 1);
    dam = 20;
    dam *= random(10);
    dam -= random(ob->GetStatLevel("coordination"));
    ob->eventReceiveDamage(this_object(),(PIERCE), dam, 0, limbname);
    if(!ob->GetInCombat()){
        ob->eventForce("attack "+this_object()->GetKeyName());
    }
    return 1;
}

int eventHoseTarget(object target){
    int repeat = 10;
    if(!target) return 0;
    //write("Hosing target: "+identify(target));
    while(repeat && !(target->GetDying())){
        eventShootDude(target);
        repeat--;
    }
    return 1;
}

int eventTargetScan(){
    object *targets;
    int targs;
    if(!environment() || !active) return 0;
    targets = filter(get_livings(environment()), (: !($1->GetInvis()) &&
                $1->GetRace() != "bot" :));
    targets = scramble_array(targets);
    targets -= ({ this_object() });
    if(!(targs = sizeof(targets))) return 0;
    if(targs > 10) targs = 10;
    else {
        eventForce("say 已锁定 "+cardinal(targs)+" 个目标。");
    }
    targs--;
    targets = targets[0..targs];
    foreach(object target in targets){
        eventHoseTarget(target);
    }
    return 1;
}

int AddLegs(){
    AddLimb("first leg", "torso", 2);
    AddLimb("second leg", "torso", 2);
    AddLimb("third leg", "torso", 2);
    return 1;
}

int ActivateTurret(){
    if(!ammo){
        write("炮塔发出咔嗒声后归于沉寂。");
        return 0;
    }
    active = 1;
    eventForce("say 炮塔现在完全武装并开始运作。");
    eventTargetScan();
    set_heart_beat(1);
    return 1;
}

protected void create() {
    sentient::create();
    SetKeyName("gun turret");
    SetId( ({"bot", "robot","turret"}) );
    SetAdjectives(({"non-player", "non player"}));
    SetShort("炮塔");
    SetLong("这是一个四英尺高的金属炮塔，安装在三脚架上，设计用于自动捕获和攻击任何移动目标，配备大型20毫米火炮。");
    SetPosition(POSITION_STANDING);
    SetLevel(1);
    SetPacifist(1);
    SetNoClean(0);
    SetRace("bot");
    SetClass("fighter");
    SetGender("neuter");
    SetPolyglot(1);
    call_out("AddLegs",0);
    SetLanguage("common",100);
    SetDefaultLanguage("common");
}

void init(){
    ::init();
}

int eventTurnOn(object ob){
    if(active){
        write("炮塔已经处于激活状态。");
        return 1;
    }
    else {
        call_out("ActivateTurret",7);
        write("你激活了炮塔。");
        eventForce("say 炮塔已激活。");
        eventForce("say 你有5秒时间到达最小安全距离。");
    }
    return 1;
}

int eventTurnOff(object ob){
    if(!active){
        write("炮塔已经处于未激活状态。");
        return 1;
    }
    else {
        write("看来这个炮塔无法被关闭。");
        //write("You deactivate the gun turret.");
        //active = 0;
    }
    return 1;
}

void heart_beat(){
    ::heart_beat();
    eventTargetScan();
}

varargs int eventReceiveDamage(mixed agent, int type, int x, int internal,
        mixed limbs){
    ActivateTurret();
    return ::eventReceiveDamage(agent, type, x, internal, limbs);
}
