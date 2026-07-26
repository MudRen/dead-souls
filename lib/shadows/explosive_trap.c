#include <lib.h>
#include <boobytraps.h>
#include <damage_types.h>

inherit LIB_BOOBYTRAP_SHADOW;

varargs mixed SpringTrap(mixed arg1, mixed arg2){
    object ob = this_player();
    mixed *stuffs = ({});
    if(!ob) ob = this_object()->GetShadowedObject();
    if(!ob || !environment(ob)) return 0;
    tell_room(environment(ob),"\n----\n轰！！！\n----\n");
    write("你触发了爆炸陷阱！");
    say(ob->GetCapName()+"触发了爆炸陷阱！");

    stuffs=ob->GetLimbs();
    foreach(string limb in stuffs){
        if(limb != "head" && limb != "torso" && limb != "neck") ob->RemoveLimb(limb,this_object());
    }

    foreach(object victim in get_livings(environment(ob))){
        victim->eventReceiveDamage("explosive device",BLUNT, random(1000)+300, 1);
    }

    return boobytrap_shadow::SpringTrap(arg1, arg2);
}

void create(){
    SetTrapType(BOOBYTRAP_OPEN | BOOBYTRAP_CLOSE |BOOBYTRAP_PICK);
}
