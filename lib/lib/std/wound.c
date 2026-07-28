#include <lib.h>
#include ROOMS_H
#include <damage_types.h>
#include <vendor_types.h>
#include <daemons.h>

inherit LIB_DUMMY;

string WoundLong(){
    int num;
    string noun, poss, verb, ret;
    string being, plural;
    object env = environment();

    if(!env){
        return "Error.";
    }

    num = env->GetLead();

    if(env == this_player()){
        noun = "你";
        verb = "";
        poss = "你的";
    }
    else {
        noun = env->GetName();
        verb = "";
        poss = possessive(env);
    }
    num = env->GetLead();
    if(!num){
        ret = noun + "正在从枪伤中恢复。";
        return ret;
    }
    if(num > 1){
        being = "有";
        plural = "个";
    }
    else {
        being = "有";
        plural = "个";
    }

    ret = noun + "被枪击受伤了。" + poss + "身上" +
        being + cardinal(this_player()->GetLead()) + plural + "弹孔。";

    return ret;
}

void create(){
    ::create();
    SetKeyName("wound");
    SetId(({"wound","firearms_wound","wounds"}));
    SetShort("一处枪伤");
    SetLong( (: WoundLong :) );
    set_heart_beat(20);
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob) || ob->GetUndead()) return 0;
    return ob->GetName() + "正在遭受枪伤的折磨。";
}

void heart_beat(){
    object ob = environment();
    int num;
    if(!ob || !living(ob)){
        this_object()->eventMove(ROOM_FURNACE);
        return;
    }
    num = ob->GetLead();
    if(!num){
        int tmp = ob->GetLead("gunshot_wounds");
        ob->AddLead("gunshot_wounds", -tmp);
        tmp = ob->GetLead("rifleshot_wounds");
        ob->AddLead("rifleshot_wounds", -tmp);
        this_object()->eventMove(ROOM_FURNACE);
        return;
    } 
    if(!RACES_D->GetNonMeatRace(ob->GetRace()) && interactive(ob)
            && !(ob->GetUndead())){
        tell_object(ob,"你的枪伤在大量出血。");
        tell_room(environment(ob), ob->GetName()+
                " bleeds heavily from "+possessive(ob)+" gunshot "+
                "wounds.",environment());
    }
}

mixed CanGet(object ob) { return "#Your hands slip on the gunshot wounds.";}
mixed CanDrop(object ob) { return "#Your hands slip on the gunshot wounds.";}
