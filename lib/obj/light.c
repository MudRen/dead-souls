#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

int Duration = 2;

int eventDematerialize(){
    object env = environment();
    object owner;
    string what;
    if(env && living(env)){
        owner = env;
        env = environment(owner);
    }
    if(!env && clonep(this_object())){
        ::eventDestruct();
        return 1;
    }
    if(owner){
        what = owner->GetName()+"的魔法光辉";
    }
    else what = "魔法光辉";
    tell_room(env,what+"逐渐消散了。", ({ owner }));
    if(owner){
        tell_object(owner,"%^BOLD%^%^CYAN%^你的魔法光辉逐渐消散了。"+
                "%^RESET%^");
    }
    ::eventDestruct();
    return 1;
}

protected void create() {
    item::create();
    AddSave( ({ "Duration" }) );
    SetKeyName("magic glow");
    SetId( ({ "magic glow spell"}));
    SetShort("明亮的光辉");
    SetLong("一个魔法光源。");
    SetMass(0);
    SetPreventDrop(1);
    SetInvis(1);
    SetRadiantLight(30);
    set_heart_beat(1);
}

int eventDeteriorate(int type){
    return type;
}

int SetDuration(int i){
    Duration = abs(i);
    return Duration;
}

void init(){
    ::init();
}

void heart_beat(){
    Duration--;
    if(clonep(this_object())){
        if(Duration < 1){
            call_out("eventDematerialize",1);
        } 
    }
}

string GetAffectLong(object ob) {
    if(!ob || !living(ob)) return 0;
    return ob->GetName() + "周围环绕着魔法光辉。";
}

int CanSell(){
    return 0;
}
