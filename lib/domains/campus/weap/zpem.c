#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>
#include <daemons.h>

inherit LIB_SHOOT;
inherit LIB_AIM;
inherit LIB_SURFACE;
inherit LIB_ACTIVATE;

nosave int active = 0;

protected void create() {
    ::create();
    SetKeyName("manipulator");
    SetId(({"gun","zpem"}));
    SetAdjectives(({"zero","point","energy","bulky","boxy","futuristic"}));
    SetShort("零点能量操纵器");
    SetLong("一个大型笨重的装置，看起来像是一种方形的、充满未来感的枪。");
    set_heart_beat(1);
    SetMass(400);
    SetDollarCost(5);
    SetVendorType(VT_WEAPON);
    SetHands(2);
    SetMaxCarry(20000);
    SetDamageType(BLUNT);
    SetWeaponType("blunt");
}

varargs mixed eventShoot(object shooter, mixed target, string direction){
    string name,patsy;
    object killer, env;
    object *inv = all_inventory(this_object());

    //tc("target: "+identify(target));

    if(!active){
        write("你必须先激活它。");
        return 1;
    }

    if(!target || direction){
        if(!sizeof(inv)){
            write("你不能那样做。");
            return 1;
        }
    }

    if(sizeof(inv)){
        write("零点能量操纵器已经在操纵"+inv->GetShort()+"了。");
        return 1;
    }

    if(living(target)){
        if(!(RACES_D->GetNonMeatRace(target->GetRace()))){
            write("零点能量操纵器对肉质物体效果不佳。");
            return 1;
        }
    }

    if(base_name(target) == LIB_CORPSE || base_name(target) == LIB_LIMB){
        write("零点能量操纵器对肉质物体效果不佳。");
        return 1;
    }

    if(target->isDummy() || target->GetMass() > 5000 ||
            target->GetPreventGet()){
        write("零点能量操纵器发出咔嗒声和嗡嗡声。");
        return 1;
    }

    if(!GetWielded()){
        write("你没有装备它。");
        return 0;
    }

    killer = this_player();
    name = killer->GetName();
    env = environment(killer);
    patsy = target->GetShort();

    tell_room(env,name+" picks up "+patsy+" with "+possessive(killer)+" "+
            "zero-point energy manipulator.",({killer,target}) );
    tell_object(killer,"你用零点能量场包围了"+patsy+"，"+
            nominative(target)+"被你的零点能量操纵器吸了起来。");
    tell_object(target,name+"用"+possessive(killer)+
            "零点能量操纵器把你吸了起来。你在它的力场中毫无办法。");

    active = 1;
    target->SetZPG(1);
    target->eventMove(this_object());
    return 1;
}

int eventTurnOff(){
    object *inv;
    if(!active){
        write("它已经处于未激活状态。");
        return 1;
    }

    inv = all_inventory();
    active = 0;
    write("你关闭了零点能量操纵器。");
    if(sizeof(inv)){
        inv->eventMove(room_environment(this_object()));
        foreach(object ob in inv){
            tell_object(ob, "你从"+this_player()->GetName()+
                    "的零点能量操纵器中被释放了。");
            tell_room(environment(this_player()), capitalize(ob->GetShort())+
                    "从"+this_player()->GetName()+"的零点能量操纵器中被释放了。", ({ ob, this_player() }) );
            write("你把"+ob->GetShort()+"从你的零点能量操纵器中释放了。");
        }
    }
    return 1;
}

int eventTurnOn(){
    if(active){
        write("它已经处于激活状态。");
        return 1;
    }
    write("你激活了零点能量操纵器。");
    say(this_player()->GetName()+" activates "+possessive(this_player())+
            " zero-point energy manipulator.");
    active = 1;
    return 1;
}


int GetZPEM(){
    return 1;
}

void init(){
    object *inv = all_inventory();
    ::init();
    if(!active){
        if(sizeof(inv) && room_environment(this_object())){
            inv->eventMove(room_environment(this_object()));
            eventDestruct();
        }
    }
}

void heart_beat(){
    object *inv = all_inventory();
    if(!active){
        if(sizeof(inv) && room_environment(this_object())){
            inv->eventMove(room_environment(this_object()));
            eventDestruct();
        }
    }
}

int CanReceive(object ob){
    object *inv = all_inventory(this_object());
    if(!active) return 0;
    if(sizeof(inv)) return 0;
    return ::CanReceive(ob);
}

mixed eventUnequip(object who){
    mixed tmp = surface::eventUnequip(who);
    if(tmp == 1){
        eventTurnOff();
    }
    return tmp;
}
